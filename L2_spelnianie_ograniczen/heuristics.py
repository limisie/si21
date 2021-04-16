from abc import ABC, abstractmethod
from collections import deque


class VariableSelector(ABC):
    def __init__(self, variables):
        self.variables = variables

    @abstractmethod
    def sorted(self):
        pass

    def next(self):
        sorted_variables = self.sorted()
        return sorted_variables[0]

    @staticmethod
    def is_unassigned(variable):
        return not variable.is_set()


class Unassigned(VariableSelector):
    def __init__(self, variables):
        super().__init__(variables)

    def sorted(self):
        return list(filter(self.is_unassigned, self.variables))


class MRV(VariableSelector):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __remaining_values(variable):
        return variable.remaining_values()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__remaining_values)


class Degree(VariableSelector):
    def __init__(self, variables):
        super().__init__(variables)

    @staticmethod
    def __constraints_involved(variable):
        return variable.active_constraints()

    def sorted(self):
        return sorted(filter(self.is_unassigned, self.variables), key=self.__constraints_involved)


class ValuesSelector:

    def sorted(self, variable):
        return variable.domain.copy()

    def next(self, variable):
        return self.sorted(variable)[0]


class LCV(ValuesSelector):

    @staticmethod
    def __least_constraining_value(variable):
        def key(value):
            return variable.constrained_variables_size(value)

    def sorted(self, variable):
        return sorted(variable.domain, key=self.__least_constraining_value(variable))
