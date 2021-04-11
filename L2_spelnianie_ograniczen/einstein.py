from csp import *

DOMAIN = [1, 2, 3, 4, 5]
NATIONALITIES = ['norwegian', 'english', 'dutch', 'german', 'swede']
COLORS = ['red', 'white', 'yellow', 'blue', 'green']
DRINKS = ['tea', 'milk', 'water', 'beer', 'coffee']
SMOKES = ['light', 'cigar', 'pipe', 'no filter', 'menthol']
ANIMALS = ['cats', 'birds', 'dogs', 'horses', 'fish']
FEATURES = [NATIONALITIES, COLORS, DRINKS, SMOKES, ANIMALS]


class Einstein(CSP):
    def __init__(self, constraints):
        super().__init__()
        self.domain = DOMAIN.copy()

        for feature in FEATURES:
            new_constraints = []
            for variable_name in feature:
                variable = Feature(variable_name, DOMAIN.copy(), [])
                constraint = Constraint(NOT_EQUALS, variable)

                self.variables.append(variable)
                new_constraints.append(constraint)

            for i, variable_name in enumerate(feature):
                temp = new_constraints.copy()
                temp.pop(i)
                variable = self.get_variable(variable_name)
                variable.constraints = temp

        for constraint in constraints:
            mode = constraint[0]

            if mode is ASSIGN:
                variable_name, value = constraint[1:]
                variable = self.get_variable(variable_name)
                new_constraint = Constraint(0, value=value)

                variable.add_constraint(new_constraint)

            if mode is EQUALS:
                variable_names = constraint[1:]
                variable1 = self.get_variable(variable_names[0])
                variable2 = self.get_variable(variable_names[1])
                new_constraint1 = Constraint(1, variable=variable2)
                new_constraint2 = Constraint(1, variable=variable1)

                variable1.add_constraint(new_constraint1)
                variable2.add_constraint(new_constraint2)

            if mode is ABSOLUTE:
                variable_names = constraint[1:3]
                value = constraint[3]
                variable1 = self.get_variable(variable_names[0])
                variable2 = self.get_variable(variable_names[1])

                variable1.add_constraint(
                    Constraint(3, variable2, value))
                variable2.add_constraint(
                    Constraint(3, variable1, value))

            if mode is SUBTRACTION:
                variable_names = constraint[1:3]
                value = constraint[3]
                variable1 = self.get_variable(variable_names[0])
                variable2 = self.get_variable(variable_names[1])

                variable1.add_constraint(
                    Constraint(4, variable2, value))
                variable2.add_constraint(
                    Constraint(4, variable1, -value))


class Feature(Variable):
    def __init__(self, name, domain, constraints):
        super().__init__(name, domain, constraints)
