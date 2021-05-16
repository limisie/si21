import math
import time
from abc import ABC, abstractmethod
from copy import deepcopy


class Player(ABC):

    def __init__(self, name):
        self.name = name
        self.nr = -1
        self.game = None
        self.bank = -1

    def setup(self, nr, bank, game):
        self.nr = nr
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

    def alfa(self, alfa, beta, score):
        return False, 0, 0

    def beta(self, alfa, beta, score):
        return False, 0, 0

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

        self.visited_count = 1
        self.nodes_visited = []
        self.times = []

    def select(self, moves):
        start_time = time.time()

        game = deepcopy(self.game)
        self.min_max(game, self.level, self)

        self.save_stats(start_time)
        return self.move

    def min_max(self, game, depth, player):
        return self.max(game, depth, player)

    def min(self, old_game, depth, player, alfa=-math.inf, beta=math.inf):
        if depth == 0 or old_game.end_condition():
            return old_game.score(self)

        children = old_game.get_legal_moves(player)
        opponent = old_game.get_opponent(player)
        best_score = math.inf

        for child in children:
            self.visited_count += 1
            game = deepcopy(old_game)
            game.move(child)
            score = self.max(game, depth - 1, opponent, alfa, beta)
            print(f'{depth - 1}: {score}')
            if score < best_score:
                best_score = score
                if depth == self.level:
                    self.move = child
            prune, alfa, beta = self.beta(alfa, beta, score)
            if prune:
                break
        return best_score

    def max(self, old_game, depth, player, alfa=-math.inf, beta=math.inf):
        if depth == 0 or old_game.end_condition():
            return old_game.score(self)

        children = old_game.get_legal_moves(player)
        opponent = old_game.get_opponent(player)
        best_score = -math.inf

        for child in children:
            self.visited_count += 1
            game = deepcopy(old_game)
            game.move(child)
            score = self.min(game, depth - 1, opponent, alfa, beta)
            print(f'{depth - 1}: {score}')
            if score > best_score:
                best_score = score
                if depth == self.level:
                    self.move = child
            prune, alfa, beta = self.alfa(alfa, beta, score)
            if prune:
                break
        return best_score

    def save_stats(self, start_time):
        end_time = time.time()
        self.times.append(end_time - start_time)
        self.nodes_visited.append(self.visited_count)
        self.visited_count = 1


class AlfaBeta(MinMax):
    def __init__(self, name, level):
        super().__init__(name, level)

    def alfa(self, alfa, beta, score):
        prune = False
        alfa = max(alfa, score)
        if alfa >= beta:
            prune = True
        return prune, alfa, beta

    def beta(self, alfa, beta, score):
        prune = False
        beta = min(beta, score)
        if beta <= alfa:
            prune = True
        return prune, alfa, beta
