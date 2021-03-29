import copy
from itertools import product


SELECT_UNSIGNED = 0
MOST_CONSTRAINED_VARIABLE = 1
MOST_CONSTRAINING_VARIABLE = 2

EQUALS = 0
NOT_EQUALS = 1


class CSP:
    def __init__(self, heuristic):
        self.heuristic = heuristic
        self.variables = []
        self.results = []
        self.domain = []

    @staticmethod
    def is_valid(variables):
        for variable in variables:
            if not variable.is_valid():
                return False
        return True

    @staticmethod
    def is_set(variable):
        return variable.value is None

    @staticmethod
    def remaining_values(variable):
        return len(variable.domain)

    @staticmethod
    def constraining_variables(variable):
        constraining_variables = 0
        for constraint in variable.constraints:
            if constraint[1].value is None:
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

    def backtracking_iterative(self):
        temp = product(self.domain, repeat=len(self.variables))

        for solution in temp:
            for i, value in enumerate(solution):
                if not self.variables[i].value == value:
                    self.variables[i].value = value
            if self.is_valid(self.variables):
                print(self.variables)
                print()
                self.results.append(copy.deepcopy(self.variables))

    def backtracking_recursive(self):
        return self.__backtracking_recursive([], self.variables)

    def __backtracking_recursive(self, assignment, variables):
        if len(assignment) == len(variables):
            self.results.append(copy.deepcopy(assignment))
            return True
        result = False

        for value in self.domain:
            var = self.select_variable()

            if var.is_value_valid(value):
                var.value = value
                assignment.append(var)
                result = self.__backtracking_recursive(assignment, variables) or result
                var.value = None
                assignment.remove(var)
        return result

    def set_result(self, variables):
        self.variables = variables


class Variable:
    def __init__(self, name, domain, constraints):
        self.name = name
        self.domain = domain
        self.constraints = constraints
        self.value = None

    def is_value_valid(self, value):
        for i, constraint in enumerate(self.constraints):
            if not self.__does_satisfy(i, value):
                return False
        return True

    def __does_satisfy(self, index, value):
        mode, variable = self.constraints[index]
        satisfies = False

        if mode is EQUALS:
            satisfies = variable.value == value

        if mode is NOT_EQUALS:
            satisfies = variable.value != value

        return satisfies

    def is_valid(self):
        return self.is_value_valid(self.value)

    def is_in_domain(self, value):
        return value in self.domain

    def set_value(self, value):
        if self.is_value_valid(value):
            self.value = value
            self.domain = [value]

    def revise(self, value):
        if self.is_value_valid(value):
            self.domain.remove(value)

    def __str__(self):
        return f'\n({self.name}: {self.value}, {self.domain})'

    def __repr__(self):
        return f'\n({self.name}: {self.value})'
