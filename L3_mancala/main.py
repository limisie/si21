from mancala import *
from player import *


# player2
#       12  11  10  9   8   7
#       6   5   4   3   2   1
#   1   ---------------------   1
#       1   2   3   4   5   6
#       0   1   2   3   4   5
# player1

def main():
    player1 = Player('kaja')
    player2 = Player('ai', mode=MIN_MAX)
    game = Mancala(player1, player2)
    print(game)
    game.run()
    print(game)


if __name__ == '__main__':
    main()
