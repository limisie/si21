import copy
from heuristics import *


class Solver(ABC):
    def __init__(self, problem):
        self.problem = problem
        self.results = []
        self.variable_selector = Unassigned(self.problem.variables)
        self.value_selector = ValuesSelector()
        self.propagation = None
        self.dynamic = False

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

    def set_propagation_mode(self, mode):
        self.propagation = {
            0: None,
            1: ForwardChecking(self.problem),
            2: AC3(self.problem),
        }[mode]

    def dynamic_heuristics(self, dynamic):
        self.dynamic = dynamic


class Backtracking(Solver):
    def __init__(self, problem):
        super().__init__(problem)

    def backtracking_recursive(self):
        return self.__backtracking_recursive([], self.problem.variables)

    def __backtracking_recursive(self, assignment, variables):
        if len(assignment) == len(variables):
            self.results.append(copy.deepcopy(assignment))
            return True
        result = False

        selected_variable = self.select_variable()

        if self.propagation is not None:
            old_domain, old_domains = self.propagation.get_domains(selected_variable)
            if type(self.propagation) is AC3:
                self.propagation.ac3()

        values = self.select_values(selected_variable)

        for value in values:
            if selected_variable.is_value_valid(value):
                selected_variable.set_value(value)
                assignment.append(selected_variable)

                if type(self.propagation) is ForwardChecking:
                    self.propagation.revise(selected_variable)

                result = self.__backtracking_recursive(assignment, variables) or result

                selected_variable.value = None

                if self.propagation is not None:
                    self.propagation.restore(selected_variable, old_domain, old_domains)

                assignment.remove(selected_variable)

        return result
