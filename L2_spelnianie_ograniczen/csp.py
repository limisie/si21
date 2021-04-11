from abc import ABC

SELECT_UNSIGNED = 0
MOST_CONSTRAINED_VARIABLE = 1
MOST_CONSTRAINING_VARIABLE = 2

ASSIGN = 0
EQUALS = 1
NOT_EQUALS = 2
ABSOLUTE = 3
SUBTRACTION = 4


class CSP(ABC):
    def __init__(self):
        self.variables = []
        self.domain = []

    def set_result(self, variables):
        self.variables = variables

    @staticmethod
    def is_valid(variables):
        for variable in variables:
            if not variable.is_valid():
                return False
        return True

    def get_index(self, variable_name):
        for i, variable in enumerate(self.variables):
            if variable.name == variable_name:
                return i
        return -1

    def get_variable(self, variable_name):
        for variable in self.variables:
            if variable.name == variable_name:
                return variable
        return None

    def show(self):
        for variable in self.variables:
            print(variable)


class Variable(ABC):
    def __init__(self, name, domain, constraints):
        self.name = name
        self.domain = domain
        self.constraints = constraints
        self.value = None

    def set_value(self, value):
        if self.is_value_valid(value):
            self.value = value
            self.domain = [value]

    def is_set(self):
        return self.value is not None

    def is_value_valid(self, value):
        for constraint in self.constraints:
            if not constraint.does_satisfy(value):
                return False
        return True

    def is_valid(self):
        return self.is_value_valid(self.value)

    def is_in_domain(self, value):
        return value in self.domain

    def add_constraint(self, constraint):
        self.constraints.append(constraint)

    def remaining_values(self):
        return len(self.domain)

    def active_constraints(self):
        constrained_variables = 0

        for constraint in self.constraints:
            if not constraint.is_unary() and not constraint.variable.is_set():
                constrained_variables += 1

        return constrained_variables

    def constrained_variables_size(self, value):
        constrained_variables = 0

        for constraint in self.constraints:
            if not constraint.is_unary() and value in constraint.variable.domain:
                constrained_variables += 1

        return constrained_variables

    def __str__(self):
        return f'{self.name}: {self.value}, {self.domain}; {self.constraints}'

    def __repr__(self):
        return f'({self.name}: {self.value})'


class Constraint:

    modes = ['ASSIGN',
             'EQUALS',
             'NOT_EQUALS',
             'ABSOLUTE',
             'SUBTRACTION']

    def __init__(self, mode, variable=None, value=0):
        self.mode = mode
        self.variable = variable
        self.value = value

    def does_satisfy(self, value):
        satisfies = False
        checked = False

        if self.mode is EQUALS:
            if self.variable.value is not None:
                satisfies = value == self.variable.value
                checked = True

        if self.mode is NOT_EQUALS:
            if self.variable.value is not None:
                satisfies = value != self.variable.value
                checked = True

        if self.mode is ASSIGN:
            satisfies = value == self.value
            checked = True

        if self.mode is SUBTRACTION:
            if self.variable.value is not None:
                satisfies = value - self.variable.value == self.value
                checked = True

        if self.mode is ABSOLUTE:
            if self.variable.value is not None:
                satisfies = abs(value - self.variable.value) == self.value
                checked = True

        return satisfies or not checked

    def is_unary(self):
        return self.variable is None

    def __str__(self):
        if self.mode is ASSIGN:
            return f'({ Constraint.modes[self.mode] }: { self.value })'
        else:
            return f'({ Constraint.modes[self.mode] }: { self.variable.name }, { self.value })'

    def __repr__(self):
        return self.__str__()
