import copy
from heuristics import *
import time


class Solver(ABC):
    def __init__(self, problem):
        self.problem = problem
        self.results = []
        self.variable_selector = Unassigned(self.problem.variables)
        self.value_selector = ValuesSelector()
        self.dynamic = False
        self.start_time = None
        self.visited = 0

    def select_variable(self):
        return self.variable_selector.next()

    def select_variables(self):
        return self.variable_selector.sorted()

    def select_values(self, variable):
        return self.value_selector.sorted(variable)

    def set_variable_selector(self, mode):
        self.variable_selector = {
            0: Unassigned(self.problem.variables),
            1: MRV(self.problem.variables),
            2: Degree(self.problem.variables)
        }[mode]

    def set_value_selector(self, mode):
        self.value_selector = {
            0: ValuesSelector(),
            1: LCV()
        }[mode]

    def recursive(self):
        self.start_time = time.time()
        self.recursion([], self.problem.variables)
        print("{}, time: {}".format(self.visited, time.time() - self.start_time))

    @abstractmethod
    def recursion(self, assignment, variables):
        pass

    @abstractmethod
    def get_domains(self, variable):
        pass

    @abstractmethod
    def revise(self, variable):
        pass

    @abstractmethod
    def restore(self, variable, old_domain, old_domains):
        pass


class Backtracking(Solver):
    def __init__(self, problem):
        super().__init__(problem)

    def recursion(self, assignment, variables):
        if len(assignment) == len(variables):
            self.results.append((time.time() - self.start_time, self.visited, copy.deepcopy(assignment)))
            return True
        result = False

        selected_variable = self.select_variable()
        values = self.select_values(selected_variable)

        for value in values:
            self.visited += 1

            if selected_variable.is_value_valid(value):
                selected_variable.value = value
                assignment.append(selected_variable)

                result = self.recursion(assignment, variables) or result

                selected_variable.value = None
                assignment.remove(selected_variable)

        return result

    def get_domains(self, variable):
        pass

    def revise(self, variable):
        pass

    def restore(self, variable, old_domain, old_domains):
        pass


class ForwardChecking(Solver):
    def __init__(self, problem):
        super().__init__(problem)

    def recursion(self, assignment, variables):
        if len(assignment) == len(variables):
            end_time = time.time()
            self.results.append((end_time - self.start_time, self.visited, copy.deepcopy(assignment)))
            return True
        result = False

        selected_variable = self.select_variable()
        values = self.select_values(selected_variable)
        old_domain, old_domains = self.get_domains(selected_variable)

        for value in values:
            self.visited += 1

            if selected_variable.is_value_valid(value):
                selected_variable.set_value(value)
                assignment.append(selected_variable)

                if self.revise(selected_variable):
                    result = self.recursion(assignment, variables) or result

                selected_variable.value = None
                self.restore(selected_variable, old_domain, old_domains)
                assignment.remove(selected_variable)

        return result

    def get_domains(self, variable):
        old_domains = {}

        for constraint in variable.constraints:
            if not constraint.is_unary():
                old_domains[constraint.variable] = constraint.variable.domain.copy()

        return variable.domain.copy(), old_domains

    def revise(self, variable):
        for constraint in variable.constraints:
            if constraint.propagate_value(variable.value):
                return False
        return True

    def restore(self, variable, old_domain, old_domains):
        variable.domain = old_domain

        for constraint in variable.constraints:
            if not constraint.is_unary():
                constraint.variable.domain = old_domains[constraint.variable].copy()


class AC3(Solver):
    def __init__(self, problem):
        super().__init__(problem)

    def recursion(self, assignment, variables):
        if len(assignment) == len(variables):
            self.results.append((time.time() - self.start_time, self.visited, copy.deepcopy(assignment)))
            return True
        result = False

        selected_variable = self.select_variable()
        old_domain, old_domains = self.get_domains(selected_variable)
        self.revise()

        values = self.select_values(selected_variable)

        for value in values:
            self.visited += 1

            if selected_variable.is_value_valid(value):
                selected_variable.set_value(value)
                assignment.append(selected_variable)

                result = self.recursion(assignment, variables) or result

                selected_variable.value = None
                self.restore(selected_variable, old_domain, old_domains)
                assignment.remove(selected_variable)

        return result

    def get_domains(self, variable):
        old_domains = {}

        for variable in self.problem.variables:
            old_domains[variable] = variable.domain.copy()

        return variable.domain.copy(), old_domains

    def revise(self, variable=None):
        self.ac3()

    def ac3(self):
        queue = deque()
        all_arcs = []

        for variable in self.problem.variables:
            if not variable.is_set():
                for constraint in variable.constraints:
                    if not constraint.is_unary():
                        queue.append((variable, constraint))
                        all_arcs.append((variable, constraint))

        while queue:
            arc = queue.popleft()
            if self.remove_inconsistent_values(arc):
                for other_arc in all_arcs:
                    if other_arc[1].variable == arc[0] and other_arc not in queue:
                        queue.append(other_arc)

    @staticmethod
    def remove_inconsistent_values(arc):
        removed = False
        xi = arc[0]
        xj = arc[1].variable
        constraint = arc[1]

        for x in xi.domain:
            found = False
            for y in xj.domain:
                if constraint.do_satisfy(x, y):
                    found = True
                    break
            if not found:
                if x in xi.domain:
                    xi.domain.remove(x)
                removed = True

        return removed

    def restore(self, variable, old_domain, old_domains):
        variable.domain = old_domain

        for variable in self.problem.variables:
            variable.domain = old_domains[variable].copy()
