import copy

SELECT_UNSIGNED = 0
MOST_CONSTRAINED_VARIABLE = 1
MOST_CONSTRAINING_VARIABLE = 2


class CSP:
    def __init__(self, heuristic, problem):
        self.heuristic = heuristic
        self.problem = problem
        self.variables = problem.variables
        self.results = []

    @staticmethod
    def is_set(variable):
        return variable.value is None

    @staticmethod
    def remaining_values(variable):
        return len(variable.domain)

    @staticmethod
    def constraining_variables(variable):
        constraining_variables = 0
        for neighbour in variable.connected_variables:
            if neighbour.value is None:
                constraining_variables += 1
        return constraining_variables

    @staticmethod
    def least_constraining_value(variable):
        constrains = [0] * len(variable.domain)
        for neighbour in variable.connected_variables:
            for i, value in enumerate(variable.domain):
                if value in neighbour.domain:
                    constrains[i] += 1
        return variable.domain[constrains.index(min(constrains))]

    def __unassigned_variables(self):
        return list(filter(self.is_set, self.variables))

    def __minimum_remaining_values(self):
        return sorted(self.__unassigned_variables(), key=self.remaining_values)

    def __most_constraining_values(self):
        return sorted(self.__unassigned_variables(), key=self.constraining_variables)

    def select_variable(self):
        return {
            0: self.__unassigned_variables(),
            1: self.__minimum_remaining_values(),
            2: self.__most_constraining_values()
        }[self.heuristic][0]

    def backtracking(self):
        return self.__backtracking_recursive([], self.variables)

    def __backtracking_recursive(self, assignment, variables):
        if len(assignment) == len(variables):
            self.results.append(copy.deepcopy(assignment))
            return True
        is_complete = False

        var = self.select_variable()
        for value in self.problem.domain:
            if var.is_value_valid(value):
                var.value = value
                assignment.append(var)
                result = self.__backtracking_recursive(assignment, variables) or is_complete
                var.value = None
                assignment.remove(var)
        return is_complete

    def set_result(self, variables):
        self.problem.variables = variables
