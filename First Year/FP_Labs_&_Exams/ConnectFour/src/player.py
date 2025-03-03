import random

from board import Board
from exceptions import InvalidInputException


class Player:
    def __init__(self, player_symbol: str, connect4_board: Board()):
        self._player_symbol = player_symbol
        self._connect4_board = connect4_board


class HumanPlayer(Player):
    def make_move(self, column: str):
        """
        Makes the human player's move on the choosen column
        :param column: The column player chose
        """
        if not column.isnumeric():
            raise InvalidInputException
        self._connect4_board.make_move(int(column) - 1, self._player_symbol)


class ComputerPlayer(Player):
    def make_move(self):
        """
        Makes the computer player's move trying to do the best one and if it cannot will chose a ranom one
        """
        column = self.best_move()
        if column == -1:
            column = random.randint(0, self._connect4_board.column_size - 1)
        self._connect4_board.make_move(column, self._player_symbol)

    def best_move(self):
        """
        Trying to win or to block the opponent
        :return: The best column to put the next piece
        """
        empty_space = ' '
        human_player_symbol = 'O'
        computer_player_symbol = 'X'
        # winning move
        for i in range(self._connect4_board.row_size):
            for j in range(self._connect4_board.column_size):
                if i == self._connect4_board.row_size - 1 and self._connect4_board.place(i, j) == empty_space:
                    self._connect4_board.make_move(j, computer_player_symbol)
                    if self._connect4_board.check_winning(computer_player_symbol):
                        self._connect4_board.undo_move(i, j, computer_player_symbol)
                        return j
                    self._connect4_board.undo_move(i, j, computer_player_symbol)
                elif self._connect4_board.place(i, j) == empty_space and self._connect4_board.place(i + 1,
                                                                                                    j) != empty_space:
                    self._connect4_board.make_move(j, computer_player_symbol)
                    if self._connect4_board.check_winning(computer_player_symbol):
                        self._connect4_board.undo_move(i, j, computer_player_symbol)
                        return j
                    self._connect4_board.undo_move(i, j, computer_player_symbol)

        # Block move
        for i in range(self._connect4_board.row_size):
            for j in range(self._connect4_board.column_size):
                if i == self._connect4_board.row_size - 1 and self._connect4_board.place(i, j) == empty_space:
                    self._connect4_board.make_move(j, human_player_symbol)
                    if self._connect4_board.check_winning(human_player_symbol):
                        self._connect4_board.undo_move(i, j, human_player_symbol)
                        return j
                    self._connect4_board.undo_move(i, j, human_player_symbol)
                elif self._connect4_board.place(i, j) == empty_space and self._connect4_board.place(i + 1,
                                                                                                    j) != empty_space:
                    self._connect4_board.make_move(j, human_player_symbol)
                    if self._connect4_board.check_winning(human_player_symbol):
                        self._connect4_board.undo_move(i, j, human_player_symbol)
                        return j
                    self._connect4_board.undo_move(i, j, human_player_symbol)
        return -1
