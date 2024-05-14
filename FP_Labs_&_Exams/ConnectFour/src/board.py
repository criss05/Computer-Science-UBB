from texttable import Texttable

from exceptions import OutsideOfBoundsError, ColumnFullError


class Board:
    def __init__(self, columns_size: int = 7, rows_size: int = 6):
        self.__column_size = columns_size
        self.__row_size = rows_size
        self.__board = [[' ' for _ in range(self.__column_size)] for _ in range(self.__row_size)]

    def place(self, row, column):
        return self.__board[row][column]

    @property
    def column_size(self) -> int:
        return self.__column_size

    @property
    def row_size(self) -> int:
        return self.__row_size

    def __str__(self):
        conect4_board = Texttable()
        header = [str(i + 1) for i in range(self.__column_size)]
        conect4_board.header(header)
        for i in range(self.__row_size):
            row = self.__board[i]
            conect4_board.add_row(row)
        return conect4_board.draw()

    def make_move(self, column: int, player_symbol: str):
        """
        Puts the player symbol on the board on the given column
        :param column: The column player choose to put the move
        :param player_symbol: The player symbol
        :raise:
        """
        empty_space = ' '
        if not (0 <= column < self.__column_size):
            raise OutsideOfBoundsError()
        if not (self.__board[0][column] == empty_space):
            raise ColumnFullError()
        for i in range(self.__row_size):
            if self.__board[i][column] == empty_space and i == self.__row_size - 1:
                self.__board[i][column] = player_symbol
            elif self.__board[i][column] == empty_space and self.__board[i + 1][column] != empty_space:
                self.__board[i][column] = player_symbol

    def undo_move(self, row: int, column: int, player_symbol: str):
        """
        Deletes the move made on the row and column given, if there is the symbol of the player you want to undo move
        :param row: The row to delete the piece
        :param column: The columnn to delete the piece
        :param player_symbol: The symbol of the player for deleting
        """
        if self.__board[row][column] == player_symbol:
            self.__board[row][column] = ' '

    def check_winning(self, player_symbol: str) -> bool:
        """
        Checking if the player won the game
        :param player_symbol: The player's symbol
        :return: True if the player won , False otherwise
        """
        # checking for rows
        for i in range(self.__row_size):
            for j in range(self.__column_size - 3):
                if self.__board[i][j] == self.__board[i][j + 1] == self.__board[i][j + 2] == \
                        self.__board[i][j + 3] == player_symbol:
                    return True

        # checking for columns
        for i in range(self.__row_size - 3):
            for j in range(self.__column_size):
                if self.__board[i][j] == self.__board[i + 1][j] == self.__board[i + 2][j] == \
                        self.__board[i + 3][j] == player_symbol:
                    return True

        # Checking for principal diagonal
        for i in range(self.__row_size - 3):
            for j in range(self.__column_size - 3):
                if self.__board[i][j] == self.__board[i + 1][j + 1] == self.__board[i + 2][j + 2] == \
                        self.__board[i + 3][
                            j + 3] == player_symbol:
                    return True

        # checking for secondary diagonal
        for i in range(3, self.__row_size):
            for j in range(self.__column_size - 3):
                if self.__board[i][j] == self.__board[i - 1][j + 1] == self.__board[i - 2][j + 2] == \
                        self.__board[i - 3][j + 3] == player_symbol:
                    return True
        return False

    def check_board_full(self) -> bool:
        """
        Checks if the board is full
        :return: True if the board is full, False otherwise
        """
        empty_space = ' '
        board_full = True
        for row in self.__board:
            if empty_space in row:
                board_full = False
        return board_full
