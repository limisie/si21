import copy
from heuristics import *


class Solver(ABC):
    def __init__(self, problem):
        self.problem = problem
        self.results = []
        self.variable_selector = Unassigned(self.problem.variables)
        self.value_selector = None

    def select_variable(self):
        return self.variable_selector.next()

    def select_value(self):
        return self.value_selector.next()


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

        for value in self.problem.domain:
            var = self.select_variable()

            if var.is_value_valid(value):
                var.value = value
                assignment.append(var)
                result = self.__backtracking_recursive(assignment, variables) or result
                var.value = None
                assignment.remove(var)
        return result
