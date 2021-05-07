import random

DEFAULT = 0
RANDOM = 1


class Mancala:
    def __init__(self, player1, player2, first_move=DEFAULT, pits=6, seed=4):
        player1.bank = pits
        player2.bank = (2 * pits) + 1
        self.players = (player1, player2)
        self.pits = pits
        self.board = [seed] * pits + [0] + [seed] * pits + [0]

        self.current_player_index = {
            DEFAULT: 0,
            RANDOM: random.randint(0, 1)
        }[first_move]
        self.round_blocked = False

    def run(self):
        while self.is_move_possible() or self.round_blocked:
            self.round()
            # print(self)
        self.count_points()
        self.announce_winner()

    def round(self):
        if not self.round_blocked:
            self.move()
        else:
            self.round_blocked = False
        self.switch_players()

    def move(self):
        player = self.players[self.current_player_index]
        opponent = self.get_opponent(player)

        pit = player.select_pit(self.board, self.get_legal_moves(player))
        seeds = self.board[pit]

        self.board[pit] = 0
        while seeds > 0:
            pit = (pit + 1) % len(self.board)
            if not pit == opponent.bank:
                self.board[pit] += 1
                seeds -= 1

        first, last = self.get_player_pits(player)
        if first <= pit <= last and self.board[pit] == 1:
            opposite_pit = self.get_opposite_pit(pit)
            self.board[player.bank] += self.board[opposite_pit]
            self.board[opposite_pit] = 0
        elif pit == player.bank:
            self.round_blocked = True

    def switch_players(self):
        self.current_player_index = (self.current_player_index + 1) % 2

    def get_player_pits(self, player):
        first_pit = (player.nr - 1) * (self.pits + 1)
        last_pit = player.nr * (self.pits + 1) - 2
        return first_pit, last_pit

    def get_legal_moves(self, player):
        moves = []
        first, last = self.get_player_pits(player)
        for pit in range(first, last + 1):
            if self.board[pit] > 0:
                moves.append(pit)
        return moves

    def is_move_possible(self):
        player = self.players[self.current_player_index]
        return self.get_legal_moves(player)

    def get_opponent(self, player):
        return self.players[player.nr % 2]

    def get_opposite_pit(self, pit):
        return self.pits * 2 - pit

    def get_points(self, player):
        return self.board[player.bank]

    def count_points(self):
        player = self.players[self.current_player_index]
        opponent = self.get_opponent(player)

        first, last = self.get_player_pits(opponent)
        extra_points = sum(self.board[first:last + 1])
        self.board[player.bank] += extra_points

        for pit in range(first, last + 1):
            self.board[pit] = 0

    def announce_winner(self):
        points = (self.get_points(self.players[0]), self.get_points(self.players[1]))
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
