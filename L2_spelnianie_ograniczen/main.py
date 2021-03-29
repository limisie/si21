import csp as obj
import map
from einstein import *
from constraint import *

NODE_DOMAIN_3 = ['red', 'yellow', 'blue']
NODE_DOMAIN_4 = ['red', 'yellow', 'blue', 'purple']

# CONSTRAINTS = [Constraint([('nationality', 'norwegian'), ('nr', 1)]),
#                Constraint([('nationality', 'english'), ('color', 'red')]),
#                Constraint([('nationality', 'dutch'), ('drink', 'tea')]),
#                Constraint([('color', 'yellow'), ('smoke', 'cigar')]),
#                Constraint([('nationality', 'german'), ('smoke', 'pipe')]),
#                Constraint([('drink', 'milk'), ('nr', 3)]),
#                Constraint([('smoke', 'no filter'), ('animal', 'birds')]),
#                Constraint([('nationality', 'swede'), ('animal', 'dogs')]),
#                Constraint([('smoke', 'menthol'), ('drink', 'beer')]),
#                Constraint([('color', 'green'), ('drink', 'coffee')]),
#                Constraint([('animal', 'cats'), ('neighbour', ein.Constraint([('smoke', 'light')]))]),
#                Constraint([('color', 'blue'), ('neighbour', ein.Constraint([('nationality', 'norwegian')]))]),
#                Constraint([('color', 'yellow'), ('neighbour', ein.Constraint([('animal', 'horses')]))]),
#                Constraint([('drink', 'water'), ('neighbour', ein.Constraint([('smoke', 'light')]))])]
HEURISTICS = ['most-constrained-variable', 'most-constraining-variable']


def map_coloring():
    zad1 = map.Map(3, NODE_DOMAIN_4)
    csp = obj.CSP(0, zad1)
    csp.backtracking()
    for result in csp.results:
        csp.set_result(result)
        zad1.show()


def einstein():
    # problem = ein.Einstein(CONSTRAINTS)

    problem = Problem()
    criteria = DOMAIN['nationality'] + DOMAIN['color'] + DOMAIN['drink'] + DOMAIN['smoke'] + DOMAIN['animal']
    problem.addVariables(criteria, [1, 2, 3, 4, 5])

    # problem.addVariables('nationality', DOMAIN['nationality'])
    # problem.addVariables('nr', DOMAIN['nr'])
    # problem.addVariables('color', DOMAIN['color'])
    # problem.addVariables('drink', DOMAIN['drink'])
    # problem.addVariables('smoke', DOMAIN['smoke'])
    # problem.addVariables('animal', DOMAIN['animal'])
    #
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['nationality'])
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['nr'])
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['color'])
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['drink'])
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['smoke'])
    # problem.addConstraint(AllDifferentConstraint(), DOMAIN['animal'])

    problem.addConstraint(InSetConstraint({1}), ['norwegian'])
    problem.addConstraint(InSetConstraint({3}), ['milk'])
    problem.addConstraint(lambda d, t: d == t, ('dutch', 'tea'))
    problem.addConstraint(lambda y, c: y == c, ('yellow', 'cigar'))
    problem.addConstraint(lambda g, p: g == p, ('german', 'pipe'))
    problem.addConstraint(lambda f, b: f == b, ('no filter', 'birds'))
    problem.addConstraint(lambda s, d: s == d, ('swede', 'dogs'))
    problem.addConstraint(lambda m, b: m == b, ('menthol', 'beer'))
    problem.addConstraint(lambda g, c: g == c, ('green', 'coffee'))
    problem.addConstraint(lambda c, l: abs(c - l) == 1, ('cats', 'light'))
    problem.addConstraint(lambda b, n: abs(b - n) == 1, ('blue', 'norwegian'))
    problem.addConstraint(lambda y, h: abs(y - h) == 1, ('yellow', 'horses'))
    problem.addConstraint(lambda w, l: abs(w - l) == 1, ('water', 'light'))
    problem.addConstraint(lambda w, g: w - g == 1, ('white', 'green'))

    solution = problem.getSolutions()[0]

    for x in solution:
        print(x)


def main():
    einstein()


if __name__ == '__main__':
    main()
