from selectors import *

HUMAN = 0
MIN_MAX = 1
ALFA_BETA = 2


class Player:
    count = 0

    def __init__(self, name, mode=HUMAN):
        self.name = name
        self.pit_selector = {
            HUMAN: Human(self),
            MIN_MAX: MinMax(self),
            ALFA_BETA: AlfaBeta(self)
        }[mode]

        Player.count += 1
        self.nr = self.count
        self.bank = -1

    def select_pit(self, board, moves):
        return self.pit_selector.select(board, moves)

    def __str__(self):
        return f'{self.name}'
