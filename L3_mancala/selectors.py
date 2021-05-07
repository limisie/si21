from abc import ABC


class PitSelector(ABC):
    def __init__(self, player):
        self.player = player

    def select(self, board, moves):
        pass


class Human(PitSelector):
    def __init__(self, player):
        super().__init__(player)

    def select(self, board, moves):
        selected = -1
        while selected not in moves:
            print(f'{self.player}: {moves}')
            user_input = input()
            try:
                selected = int(user_input)
            except ValueError:
                selected = -1
        return selected


class MinMax(PitSelector):
    def __init__(self, player):
        super().__init__(player)

    def select(self, board, moves):
        pass


class AlfaBeta(PitSelector):
    def __init__(self, player):
        super().__init__(player)

    def select(self, board, moves):
        pass
