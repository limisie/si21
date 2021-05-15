import math
from abc import ABC, abstractmethod
from copy import deepcopy

HUMAN = 0
MIN_MAX = 1
ALFA_BETA = 2


class Player(ABC):
    count = 0

    def __init__(self, name):
        Player.count += 1
        self.nr = self.count

        self.name = name
        self.game = None
        self.bank = -1

    def setup(self, bank, game):
        self.bank = bank
        self.game = game

    def is_equal(self, player):
        equal = False
        if self.name == player.name and self.nr == player.nr:
            equal = True
        return equal

    @abstractmethod
    def select(self, moves):
        pass

    def __str__(self):
        return f'{self.name}'


class Human(Player):
    def __init__(self, name):
        super().__init__(name)

    def select(self, moves):
        selected = -1
        while selected not in moves:
            print(f'{self.name}: {moves}')
            user_input = input()
            try:
                selected = int(user_input)
            except ValueError:
                selected = -1
        return selected


class MinMax(Player):
    def __init__(self, name, level):
        super().__init__(name)
        self.level = level
        self.move = None

    def select(self, moves):
        game = deepcopy(self.game)
        self.min_max(game, self.level, self)
        return self.move

    def min_max(self, game, depth, player):
        if depth == 0 or game.end_condition():
            return game.score(self)

        old_game = game
        children = game.get_legal_moves(player)
        opponent = game.get_opponent(player)
        if player.is_equal(self):
            best_score = -math.inf
        else:
            best_score = math.inf

        for child in children:
            game = deepcopy(old_game)
            game.move(child)
            score = self.min_max(game, depth - 1, opponent)
            # print(f'{depth-1}: {score}')
            if player.is_equal(self):
                if score > best_score:
                    best_score = score
                    if depth == self.level:
                        self.move = child
            else:
                if score < best_score:
                    best_score = score
                    if depth == self.level:
                        self.move = child
        return best_score


class AlfaBeta(Player):
    def __init__(self, name):
        super().__init__(name)

    def select(self, moves):
        pass
