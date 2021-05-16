import random

DEFAULT = 0
RANDOM = 1


class Mancala:
    def __init__(self, player1, player2, pits=6, seed=4, first_move=DEFAULT, first_player=DEFAULT):
        player1.setup(1, pits, self)
        player2.setup(2, (2 * pits) + 1, self)
        self.players = (player1, player2)
        self.pits = pits
        self.board = [seed] * pits + [0] + [seed] * pits + [0]

        self.first_move = {
            DEFAULT: False,
            RANDOM: True
        }[first_move]

        self.current_player_index = {
            DEFAULT: 0,
            RANDOM: random.randint(0, 1)
        }[first_player]
        self.round_blocked = False

    def end_condition(self):
        end = not self.is_move_possible() and not self.round_blocked
        if end:
            self.count_points()
        return end

    def run(self):
        while not self.end_condition():
            if not self.round_blocked:
                self.turn()
            else:
                self.round_blocked = False
                self.switch_players()
        # self.count_points()
        self.announce_winner()

    def turn(self):
        player = self.players[self.current_player_index]
        moves = self.get_legal_moves(player)

        if self.first_move:
            move = moves[random.randint(0, len(moves))]
            self.first_move = False
        else:
            move = player.select(moves)

        self.move(move)
        print(f'MOVE: {player}: {move}')
        print(self)

    def move(self, pit):
        if not self.round_blocked:
            player = self.players[self.current_player_index]
            opponent = self.get_opponent(player)
            seeds = self.board[pit]
            self.board[pit] = 0
            while seeds > 0:
                pit = (pit + 1) % len(self.board)
                if not pit == opponent.bank:
                    self.board[pit] += 1
                    seeds -= 1

            self.capture(pit, player)

            if pit == player.bank:
                self.round_blocked = True
        else:
            self.round_blocked = False
        self.switch_players()

    def capture(self, pit, player):
        first, last = self.get_player_pits(player)
        if first <= pit <= last and self.board[pit] == 1:
            opposite_pit = self.get_opposite_pit(pit)
            self.board[player.bank] += self.board[opposite_pit]
            self.board[opposite_pit] = 0

    def switch_players(self):
        self.current_player_index = (self.current_player_index + 1) % 2

    def get_player_pits(self, player):
        first_pit = (player.nr - 1) * (self.pits + 1)
        last_pit = player.nr * (self.pits + 1) - 2
        return first_pit, last_pit

    def get_legal_moves(self, player):
        moves = []
        if self.round_blocked:
            moves.append(-1)
        else:
            first, last = self.get_player_pits(player)
            for pit in range(first, last + 1):
                if self.board[pit] > 0:
                    moves.append(pit)
        return moves

    def is_move_possible(self):
        player = self.players[self.current_player_index]
        if self.get_legal_moves(player):
            return True
        else:
            return False

    def get_opponent(self, player):
        return self.players[player.nr % 2]

    def get_player_index(self, player):
        return (player.nr + 1) % 2

    def get_opposite_pit(self, pit):
        return self.pits * 2 - pit

    def get_points(self, player):
        return self.board[player.bank]

    def count_points(self):
        player = self.players[self.current_player_index]
        opponent = self.get_opponent(player)

        first, last = self.get_player_pits(opponent)
        extra_points = sum(self.board[first:last + 1])
        self.board[opponent.bank] += extra_points

        for pit in range(first, last + 1):
            self.board[pit] = 0

    def score(self, player):
        return self.board[player.bank] - self.board[self.get_opponent(player).bank]

    def announce_winner(self):
        points = (self.get_points(self.players[0]), self.get_points(self.players[1]))
        if points[0] == points[1]:
            print('It\'s a tie!')
        else:
            print(f'The winner is {self.players[points.index(max(points))]}: {max(points)}p\n'
                  f'The loser is {self.players[points.index(min(points))]}: {min(points)}p\n')

    def __str__(self):
        console_board = f'{self.players[1]}\n\t\t'
        console_board += '\t'.join([str(pit) for pit in self.board[self.pits * 2:self.pits:-1]])
        console_board += f'\n\t{self.board[-1]}\t'
        console_board += ''.join(['----' for _ in self.board[:self.pits - 1]])
        console_board += f'-\t{self.board[self.pits]}\n\t\t'
        console_board += '\t'.join([str(x) for x in self.board[:self.pits]])
        console_board += f'\n{self.players[0]}\n'
        return console_board
