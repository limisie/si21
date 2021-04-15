from abc import ABC, abstractmethod
from collections import deque


class Heuristic(ABC):
    def __init__(self, variables):
        self.variables = variables

    @abstractmethod
    def sorted(self):
        pass

    def next(self):
        sorted_variables = self.sorted()
        return sorted_variables[0]

    @staticmethod
    def is_unassigned(variable):
        return not variable.is_set()


class Unassigned(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    def sorted(self):
        return list(filter(self.is_unassigned, self.variables))


class MRV(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __remaining_variables(variable):
        return variable.remaining_values()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__remaining_variables)


class Degree(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __constraints_involved(variable):
        return variable.active_constraints()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__constraints_involved, reverse=True)


class ValuesSelector:

    def sorted(self, variable):
        return variable.domain.copy()

    def next(self, variable):
        return self.sorted(variable)[0]


class LCV(ValuesSelector):

    def __least_constraining_value(self, variable):
        def key(value):
            return variable.constrained_variables_size(value)

    def sorted(self, variable):
        return sorted(variable.domain, key=self.__least_constraining_value(variable))


class Propagation(ABC):
    def __init__(self, problem):
        self.problem = problem

    @abstractmethod
    def revise(self, variable):
        pass

    @abstractmethod
    def get_domains(self, variable):
        pass

    @abstractmethod
    def restore(self, variable, old_domain, old_domains):
        pass


class ForwardChecking(Propagation):
    def __init__(self, problem):
        super().__init__(problem)

    def get_domains(self, variable):
        old_domains = {}

        for constraint in variable.constraints:
            if not constraint.is_unary():
                old_domains[constraint.variable] = constraint.variable.domain.copy()

        return variable.domain.copy(), old_domains

    def revise(self, variable):
        if variable.is_set():
            for constraint in variable.constraints:
                constraint.propagate_value(variable.value)

    def restore(self, variable, old_domain, old_domains):
        variable.domain = old_domain

        for constraint in variable.constraints:
            if not constraint.is_unary():
                constraint.variable.domain = old_domains[constraint.variable].copy()


class AC3(Propagation):
    def __init__(self, problem):
        super().__init__(problem)

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
