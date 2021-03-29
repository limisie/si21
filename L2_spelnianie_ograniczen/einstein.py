# zbiór zmiennych: X = { narodowość, numer domu, kolor domu, napój, palenie, zwierzę }
# dziedzina każdej zmiennej:
# 	narodowość:     D0 = { norweg, anglik, duńczyk, niemiec, szwed } dla X0
# 	nr domu:        D1 ={ 1, 2, 3, 4, 5 } dla X1
# 	kolor domu:     D2 ={ czerwony, biały, żółty, niebieski, zielony } dla X2
# 	napój:          D3 ={ herbata, mleko, woda, piwo, kawa } dla X3
# 	palenie:        D4 ={ light, cygaro, fajka, bez filtra, mentol } dla X4
# 	zwierzę:        D5 ={ koty, ptaki, psy, konie, rybki } dla X5
# ograniczenia: każda wartość może wystąpić tylko raz: AllDiff( x1, x2, x3, x1, x2)
import copy

VARIABLES = ['nationality', 'nr', 'color', 'drink', 'smoke', 'animal']
DOMAIN = {
             'nationality': ['norwegian', 'english', 'dutch', 'german', 'swede'],
             'nr': [1, 2, 3, 4, 5],
             'color': ['red', 'white', 'yellow', 'blue', 'green'],
             'drink': ['tea', 'milk', 'water', 'beer', 'coffee'],
             'smoke': ['light', 'cigar', 'pipe', 'no filter', 'menthol'],
             'animal': ['cats', 'birds', 'dogs', 'horses', 'fish']
        }


class Einstein:
    def __init__(self, constraints):
        self.domain = copy.deepcopy(DOMAIN)
        self.entities = []
        self.constraints = constraints.copy()

        for number in DOMAIN['nr']:
            self.entities.append(Entity(number, self))

        # for constraint in self.constraints:
        #     if

    def show(self):
        for entity in self.entities:
            print(entity)
        print(self.domain)

    @staticmethod
    def variable_of_value(value):
        for variable in VARIABLES:
            if value in DOMAIN[variable]:
                return variable
        return None

    @staticmethod
    def is_failure(variables):
        for variable in variables:
            for neighbour in variable.connected_variables:
                if variable.value == neighbour.value:
                    return True
        return False


class Constraint:
    def __init__(self, values):
        self.constraint = {
            'nationality': None,
            'nr': None,
            'color': None,
            'drink': None,
            'smoke': None,
            'animal': None,
            'neighbour': Constraint([])
        }

        for value in values:
            self.constraint[value[0]] = value[1]


class Entity:
    def __init__(self, number, problem):
        self.problem = problem
        self.problem.domain['nr'].remove(number)

        self.variables = {
            'nationality': None,
            'nr': number,
            'color': None,
            'drink': None,
            'smoke': None,
            'animal': None
        }

    def is_value_of_variable_valid(self, variable, value):
        return value in self.problem.domain[variable]

    def is_value_valid(self, value):
        variable = Einstein.variable_of_value(value)
        return self.is_value_of_variable_valid(variable, value)

    def set_value_of_variable(self, variable, value):
        if self.is_value_of_variable_valid(variable, value):
            self.variables[variable] = value
            self.problem.domain[variable].remove(value)

    def set_value(self, value):
        variable = Einstein.variable_of_value(value)
        self.set_value_of_variable(variable, value)

    def __str__(self):
        return f'\n({self.variables["nr"]}, ' \
               f'{self.variables["nationality"]},' \
               f'{self.variables["color"]},' \
               f'{self.variables["drink"]},' \
               f'{self.variables["smoke"]},' \
               f'{self.variables["animal"]})'

    def __repr__(self):
        return f'\n({self.variables["nr"]})'
