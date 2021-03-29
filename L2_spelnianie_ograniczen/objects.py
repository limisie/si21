import planarity
import networkx as nx
import matplotlib.pyplot as plt


class CSP:
    def __init__(self, heuristic, problem):
        self.heuristic = heuristic
        self.problem = problem
        self.variables = problem.variables()
        self.assignment = []
        self.results = []

    @staticmethod
    def is_set(variable):
        return variable.value is None

    @staticmethod
    def remaining_values(variable):
        return len(variable.domain)

    @staticmethod
    def constraining_variables(variable):
        constraining_variables = 0
        for neighbour in variable.connected_variables:
            if neighbour.value is None:
                constraining_variables += 1
        return constraining_variables

    @staticmethod
    def least_constraining_value(variable):
        constrains = [0] * len(variable.domain)
        for neighbour in variable.connected_variables:
            for i, value in enumerate(variable.domain):
                if value in neighbour.domain:
                    constrains[i] += 1
        return variable.domain[constrains.index(min(constrains))]

    def __unassigned_variables(self):
        return list(filter(self.is_set, self.variables))

    def __minimum_remaining_values(self):
        return sorted(self.__unassigned_variables(), key=self.remaining_values)

    def __most_constraining_values(self):
        return sorted(self.__unassigned_variables(), key=self.constraining_variables)

    def select_variable(self):
        return {
            0: self.__unassigned_variables(),
            1: self.__minimum_remaining_values(),
            2: self.__most_constraining_values()
        }[self.heuristic][0]

    @staticmethod
    def is_failure(variables):
        for variable in variables:
            for neighbour in variable.connected_variables:
                if variable.value == neighbour.value:
                    return True
        return False

    def backtracking(self):
        return self.__backtracking_recursive(self.assignment, self.variables)

    def __backtracking_recursive(self, assignment, variables):
        if len(assignment) == len(variables):
            self.problem.variables = assignment
            return assignment
        var = self.select_variable()
        for value in var.domain:
            if var.is_value_valid(value):
                var.value = value
                assignment.append(var)
                if not CSP.is_failure(assignment):
                    return self.__backtracking_recursive(assignment, variables)
                else:
                    assignment.remove(var)
        return None


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

    def show_graph(self):
        self.__set_graph_colors()
        nx.draw(self.graph, node_color=self.color_map, with_labels=True)
        plt.show()

    def variables(self):
        return self.nodes

    def set_value(self, index, value):
        self.nodes[index].set_value(value)


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
        return f'({self.name}: {self.value}, {self.domain})\n'
