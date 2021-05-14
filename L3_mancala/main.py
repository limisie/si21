from mancala import *
from player import *


# player2
#       12  11  10  9   8   7
#  13   ---------------------   6
#       0   1   2   3   4   5
# player1

def main():
    player1 = Player('minmax2', mode=MIN_MAX, level=2)
    player2 = Player('minmax4', mode=MIN_MAX, level=3)
    game = Mancala(player1, player2)
    print(game)
    game.run()
    print(game)


if __name__ == '__main__':
    main()
