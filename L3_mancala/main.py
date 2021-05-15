from mancala import *
from player import *


# player2
#       12  11  10  9   8   7
#  13   ---------------------   6
#       0   1   2   3   4   5
# player1

def main():
    player1 = MinMax('minmax2', level=2)
    player2 = MinMax('minmax3', level=3)
    game = Mancala(player1, player2)
    print(game)
    game.run()
    print(game)


if __name__ == '__main__':
    main()
