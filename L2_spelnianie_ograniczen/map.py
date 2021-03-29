import planarity
import networkx as nx
import matplotlib.pyplot as plt


class Map:
    def __init__(self, n, domain):
        self.n = n
        self.nodes = []
        self.edges = set()
        self.graph = None
        self.color_map = []
        self.domain = domain.copy()

        for node in range(self.n):
            self.nodes.append(Node(node, domain))

        self.__init_planar_graph()

    def __init_planar_graph(self):
        for node in range(self.n):
            for node_to_connect in range(node + 1, self.n):
                connected = True
                self.edges.add((node, node_to_connect))

                if not planarity.is_planar(self.edges):
                    connected = False
                    self.edges.remove((node, node_to_connect))

                if connected:
                    self.nodes[node].connect(self.nodes[node_to_connect])
                    self.nodes[node_to_connect].connect(self.nodes[node])

        self.graph = nx.Graph(self.edges)

    def __set_graph_colors(self):
        self.color_map.clear()
        for node in self.graph:
            variable = self.nodes[node]
            if variable.value is not None:
                self.color_map.append(variable.value)
            else:
                self.color_map.append('white')

    def show(self):
        self.__set_graph_colors()
        nx.draw(self.graph, node_color=self.color_map, with_labels=True)
        plt.show()

    @staticmethod
    def is_failure(variables):
        for variable in variables:
            for neighbour in variable.connected_variables:
                if variable.value == neighbour.value:
                    return True
        return False


class Node:
    def __init__(self, name, domain):
        self.name = name
        self.connected_variables = set()
        self.domain = domain.copy()
        self.value = None

    def connect(self, node):
        self.connected_variables.add(node)

    def is_value_valid(self, value):
        for neighbour in self.connected_variables:
            if neighbour.value == value:
                return False
        return True

    def is_in_domain(self, value):
        return value in self.domain

    def set_value(self, value):
        if self.is_value_valid(value):
            self.value = value
            self.domain = [value]

            for neighbour in self.connected_variables:
                neighbour.revise(value)

    def revise(self, value):
        if self.is_value_valid(value):
            self.domain.remove(value)

    def __repr__(self):
        return f'\n({self.name}: {self.value})'
