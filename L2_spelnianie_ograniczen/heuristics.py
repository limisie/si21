from abc import ABC, abstractmethod


class Heuristic(ABC):
    def __init__(self, variables):
        self.variables = variables

    @abstractmethod
    def sorted(self):
        pass

    def next(self):
        return self.sorted()[0]

    @staticmethod
    def is_unassigned(variable):
        return not variable.is_set()


class Unassigned(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    def sorted(self):
        return list(filter(self.is_unassigned, self.variables))


class MRV(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __remaining_variables(variable):
        return variable.remaining_values()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__remaining_variables)


class Degree(Heuristic):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __constraints_involved(variable):
        return variable.active_constraints()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__constraints_involved, reverse=True)


class LCV(Heuristic):
    def __init__(self, domain, variable):
        super().__init__(domain)
        self.variable = variable

    def least_constraining_value(self, value):
        return self.variable.constrained_variables_size(value)

    def sorted(self):
        return sorted(self.variables, key=self.least_constraining_value)
