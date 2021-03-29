
DOMAIN = [1, 2, 3, 4, 5]
NATIONALITIES = ['norwegian', 'english', 'dutch', 'german', 'swede']
COLORS = ['red', 'white', 'yellow', 'blue', 'green']
DRINKS = ['tea', 'milk', 'water', 'beer', 'coffee']
SMOKES = ['light', 'cigar', 'pipe', 'no filter', 'menthol']
ANIMALS = ['cats', 'birds', 'dogs', 'horses', 'fish']

ASSIGN = 0
EQUALS = 1
ABSOLUTE = 1
SUBTRACTION = 2


class Einstein:
    def __init__(self, constraints):
        variables = NATIONALITIES + COLORS + DRINKS + SMOKES + ANIMALS
        self.variables = {}
        self.constraints = constraints

        for variable in variables:
            self.variables[variable] = Variable(variable, DOMAIN.copy())

    def __check_constraints(self):
        for constraint in self.constraints:
            mode = constraint[0]

            if mode == ASSIGN:
                variable = self.variables[constraint[1]]
                value = constraint[2]
                if self.__assign_value(variable, value):
                    self.constraints.remove(constraint)

            if mode == EQUALS:
                variables = [self.variables[constraint[1]], self.variables[constraint[2]]]
                if self.__set_equals(variables):
                    self.constraints.remove(constraint)

            if mode == ABSOLUTE:
                variables = [self.variables[constraint[1]], self.variables[constraint[2]]]
                result = self.variables[constraint[3]]
                if self.__check_absolute(variables, result):
                    self.constraints.remove(constraint)

            if mode == SUBTRACTION:
                variables = [self.variables[constraint[1]], self.variables[constraint[2]]]
                result = self.variables[constraint[3]]
                if self.__check_subtraction(variables, result):
                    self.constraints.remove(constraint)

    @staticmethod
    def __assign_value(variable, value):
        variable.value = value
        return True

    @staticmethod
    def __set_equals(variables):
        variables = sorted(variables, key=Einstein.domain_size)
        variables[1].domain = variables[0].domain
        return True

    @staticmethod
    def __check_absolute(variables, result):
        return abs(variables[0].value - variables[1].value) == result

    @staticmethod
    def __check_subtraction(variables, result):
        return variables[0].value - variables[1].value == result

    @staticmethod
    def domain_size(variable):
        return len(variable.domain)

    def show(self):
        for variable in self.variables:
            print(variable)


class Variable:
    def __init__(self, name, domain):
        self.name = name
        self.domain = domain
        self.value = None

    def is_value_valid(self, value):
        return value in self.domain

    def __str__(self):
        return f'\n({self.name}: {self.domain})'
