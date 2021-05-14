from selector import *

HUMAN = 0
MIN_MAX = 1
ALFA_BETA = 2


class Player:
    count = 0

    def __init__(self, name, mode=HUMAN, level=3):
        self.name = name
        self.game = None
        self.pit_selector = {
            HUMAN: Human(self),
            MIN_MAX: MinMax(self, level),
            ALFA_BETA: AlfaBeta(self)
        }[mode]

        Player.count += 1
        self.nr = self.count
        self.bank = -1

    def setup(self, bank, game):
        self.bank = bank
        self.game = game
        self.pit_selector.game = game

    def select_pit(self, moves):
        return self.pit_selector.select(moves)

    def is_equal(self, player):
        equal = False
        if self.name == player.name and self.nr == player.nr:
            equal = True
        return equal

    def __str__(self):
        return f'{self.name}'
