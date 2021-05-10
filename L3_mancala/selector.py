import math
from abc import ABC
from copy import deepcopy


class PitSelector(ABC):
    def __init__(self, player):
        self.player = player

    def select(self, moves):
        pass


class Human(PitSelector):
    def __init__(self, player):
        super().__init__(player)

    def select(self, moves):
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
    def __init__(self, player, level):
        super().__init__(player)
        self.level = level
        self.move = None

    def select(self, moves):
        game = deepcopy(self.player.game)
        self.min_max(game, self.level, self.player)
        return self.move

    def min_max(self, game, depth, player):
        if depth == 0 or game.end_condition():
            if game.end_condition():
                game.count_points()
            return game.score(self.player)

        old_game = deepcopy(game)
        children = game.get_legal_moves(player)
        opponent = game.get_opponent(player)
        if player == self.player:
            best_score = -math.inf
        else:
            best_score = math.inf

        for child in children:
            game = deepcopy(old_game)
            game.move(child)
            score = self.min_max(game, depth - 1, opponent)
            if player == self.player:
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


class AlfaBeta(PitSelector):
    def __init__(self, player):
        super().__init__(player)

    def select(self, moves):
        pass
