from map_coloring import *
from einstein import *
from solvers import Backtracking


def solve_and_show_results(problem):
    solver = Backtracking(problem)
    solver.backtracking_recursive()
    print(len(solver.results))
    for result in solver.results:
        print(result)
        problem.set_result(result)
        problem.show()


def map_coloring():
    problem = Map(SELECT_UNSIGNED, 5, 4)
    solve_and_show_results(problem)


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
    problem.show()

    solve_and_show_results(problem)


def main():
    map_coloring()
    einstein()


if __name__ == '__main__':
    main()
