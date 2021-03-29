from csp import *
import map
from einstein import *
import constraint

NODE_DOMAIN_3 = ['red', 'yellow', 'blue']
NODE_DOMAIN_4 = ['red', 'yellow', 'blue', 'purple']


def map_coloring():
    problem = map.Map(3, NODE_DOMAIN_4)
    csp = CSP(SELECT_UNSIGNED, problem)
    csp.backtracking()
    for result in csp.results:
        csp.set_result(result)
        problem.show()


def einstein():
    constraints = [
        (ASSIGN, 'norwegian', 1),
        (EQUALS, 'english', 'red'),
        (SUBTRACTION, 'white', 'green', 1),
        (EQUALS, 'dutch', 'tea'),
        (ABSOLUTE, 'light', 'cats', 1),
        (EQUALS, 'yellow', 'cigar'),
        (EQUALS, 'german', 'pipe'),
        (ASSIGN, 'milk', 3),
        (ABSOLUTE, 'light', 'water', 1),
        (EQUALS, 'no filter', 'birds'),
        (EQUALS, 'swede', 'dogs'),
        (ABSOLUTE, 'norwegian', 'blue', 1),
        (ABSOLUTE, 'horses', 'yellow', 1),
        (EQUALS, 'menthol', 'beer'),
        (EQUALS, 'green', 'coffee')]

    problem = Einstein(constraints)


def main():
    einstein()


if __name__ == '__main__':
    main()
