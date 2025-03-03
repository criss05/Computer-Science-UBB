from exceptions import Exceptions
from board import Board
from player import HumanPlayer, ComputerPlayer


class UI:
    def __init__(self):
        self.__board = Board()
        self.__human_player_symbol = 'O'
        self.__computer_playeyr_symbol = 'X'
        self.__human_player = HumanPlayer(self.__human_player_symbol, self.__board)
        self.__computer_player = ComputerPlayer(self.__computer_playeyr_symbol, self.__board)

    def start_game(self):
        print(self.__board)
        human_turn = True
        while True:
            if human_turn:
                try:
                    column = input("column: ")
                    self.__human_player.make_move(column)
                    human_turn = False
                    if self.__board.check_winning(self.__human_player_symbol):
                        print(self.__board)
                        print("Human Player has won!")
                        break
                except Exceptions as error:
                    print(error)
            else:
                self.__computer_player.make_move()
                human_turn = True
                print(self.__board)
                if self.__board.check_winning(self.__computer_playeyr_symbol):
                    print("Computer Player has won!")
                    break
            if self.__board.check_board_full():
                print("Draw!")
                break
