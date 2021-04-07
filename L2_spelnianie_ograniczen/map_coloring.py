from csp import *
import planarity
import networkx as nx
import matplotlib.pyplot as plt

COLORS = ['orange', 'y', 'skyblue', 'rebeccapurple']


class Map(CSP):
    def __init__(self, heuristic, n, m):
        super().__init__(heuristic)
        self.domain = COLORS[:m]

        self.graph = None
        self.color_map = []

        for i in range(n):
            self.variables.append(Node(i, self.domain.copy(), []))

        self.__init_planar_graph()

    def __init_planar_graph(self):
        n = len(self.variables)
        edges = set()

        for node in range(n):
            for node_to_connect in range(node + 1, n):
                edges.add((node, node_to_connect))
                connected = True

                if not planarity.is_planar(edges):
                    edges.remove((node, node_to_connect))
                    connected = False

                if connected:
                    self.variables[node].connect(self.variables[node_to_connect])
                    self.variables[node_to_connect].connect(self.variables[node])

        self.graph = nx.Graph(edges)

    def __set_graph_colors(self):
        self.color_map.clear()
        for i in self.graph:
            variable = self.variables[i]
            if variable.value is not None:
                self.color_map.append(variable.value)
            else:
                self.color_map.append('white')

    def show(self):
        self.__set_graph_colors()
        nx.draw(self.graph, node_color=self.color_map, with_labels=True)
        plt.show()


class Node(Variable):
    def __init__(self, name, domain, constraints):
        super().__init__(name, domain, constraints)

    def connect(self, node):
        self.constraints.append(Constraint(NOT_EQUALS, variable=node))
