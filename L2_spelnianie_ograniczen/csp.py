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

    def reset_domain(self, variable):
        variable.domain = self.domain.copy()

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
        self.value = value
        self.domain = [value]

    def is_set(self):
        return self.value is not None

    def is_value_valid(self, value):
        for constraint in self.constraints:
            if not constraint.does_satisfy(value):
                return False
        return True

    def is_in_domain(self, value):
        return value in self.domain

    def add_constraint(self, constraint):
        self.constraints.append(constraint)

    def remaining_values(self):
        return len(self.domain)

    def active_constraints(self):
        return len(self.get_unset_constrained_variables())

    def get_unset_constrained_variables(self):
        variables = set()

        for constraint in self.constraints:
            if not constraint.is_unary() and not constraint.variable.is_set():
                variables.add(constraint.variable)

        return list(variables)

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

    def do_satisfy(self, xi_value, xj_value):
        satisfies = False
        checked = False

        if self.mode is EQUALS:
            satisfies = xi_value == xj_value
            checked = True

        if self.mode is NOT_EQUALS:
            satisfies = xi_value != xj_value
            checked = True

        if self.mode is ASSIGN:
            satisfies = xi_value == self.value
            checked = True

        if self.mode is SUBTRACTION:
            satisfies = xi_value - xj_value == self.value
            checked = True

        if self.mode is ABSOLUTE:
            satisfies = abs(xi_value - xj_value) == self.value
            checked = True

        return satisfies or not checked

    def is_unary(self):
        return self.variable is None

    def propagate_value(self, value):
        if self.mode is EQUALS:
            if value in self.variable.domain:
                self.variable.domain = [value]

        if self.mode is NOT_EQUALS:
            if value in self.variable.domain:
                self.variable.domain.remove(value)

        if self.mode is SUBTRACTION:
            if value - self.value in self.variable.domain:
                self.variable.domain = [value - self.value]

        if self.mode is ABSOLUTE:
            new_domain = []

            new_value = value - self.value
            if new_value in self.variable.domain:
                new_domain.append(new_value)

            new_value = value + self.value
            if new_value in self.variable.domain:
                new_domain.append(new_value)

            self.variable.domain = new_domain

    def __str__(self):
        if self.mode is ASSIGN:
            return f'({ Constraint.modes[self.mode] }: { self.value })'
        else:
            return f'({ Constraint.modes[self.mode] }: { self.variable.name }, { self.value })'

    def __repr__(self):
        return self.__str__()
