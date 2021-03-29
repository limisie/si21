import objects as obj

NODE_DOMAIN_3 = ['red', 'yellow', 'blue']
NODE_DOMAIN_4 = ['red', 'yellow', 'blue', 'purple']
HEURISTICS = ['most-constrained-variable', 'most-constraining-variable']


def main():
    zad1 = obj.Map(8, NODE_DOMAIN_4)
    csp = obj.CSP(0, zad1)
    csp.backtracking()
    zad1.show_graph()


if __name__ == '__main__':
    main()
