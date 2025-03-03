from texttable import Texttable
import random


class Board:
    def __init__(self, size):
        self.__size = size
        self.__board = [[' ' for _ in range(self.__size)] for _ in range(self.__size)]
        self.snake_start()
        self.__snake_size = 3
        self.__snake_direction = 'up'

    def snake_start(self):
        middle = self.__size // 2
        self.__board[middle - 1][middle] = '*'
        self.__board[middle][middle] = '+'
        self.__board[middle + 1][middle] = '+'

    def place_apples(self, number_of_apples):
        while number_of_apples:
            row = random.randint(0, self.__size - 1)
            column = random.randint(0, self.__size - 1)
            if self.__board[row][column] == ' ':
                self.__board[row][column] = 'a'
                number_of_apples -= 1

    def make_move(self, number_of_moves):
        row_head, column_head = self.snake_head()
        row_end, column_end = self.snake_end()
        if self.__snake_direction == 'up':
            if row_head == 0 or self.__board[row_head - 1][column_head] == '+':
                return False
            if not self.__board[row_head - 1][column_head] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head - 1][column_head] = '*'
            self.__board[row_head][column_head] = '+'

        if self.__snake_direction == 'down':
            if row_head == self.__size - 1 or self.__board[row_head + 1][column_head] == '+':
                return False
            if not self.__board[row_head + 1][column_head] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head + 1][column_head] = '*'
            self.__board[row_head][column_head] = '+'

        if self.__snake_direction == 'left':
            if column_head == 0 or self.__board[row_head][column_head - 1] == '+':
                return False
            if not self.__board[row_head][column_head - 1] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head][column_head - 1] = '*'
            self.__board[row_head][column_head] = '+'

        if self.__snake_direction == 'right':
            if column_head == self.__size - 1 or self.__board[row_head][column_head + 1] == '+':
                return False
            if not self.__board[row_head][column_head + 1] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head][column_head + 1] = '*'
            self.__board[row_head][column_head] = '+'
        return True

    def snake_head(self):
        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board[i][j] == '*':
                    return i, j

    def snake_end(self):
        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board[i][j] == '+' and \
                        ((self.__board[i - 1][j] == '+' and self.__board[i + 1][j] == ' ' and self.__board[i][
                            j - 1] == ' ' and self.__board[i][j + 1] == ' ')
                         or (self.__board[i - 1][j] == ' ' and self.__board[i + 1][j] == '+' and self.__board[i][
                                    j - 1] == ' ' and self.__board[i][j + 1] == ' ') or
                         (self.__board[i - 1][j] == ' ' and self.__board[i + 1][j] == ' ' and self.__board[i][
                             j - 1] == '+' and self.__board[i][j + 1] == ' ') or
                         (self.__board[i - 1][j] == ' ' and self.__board[i + 1][j] == ' ' and self.__board[i][
                             j - 1] == ' ' and self.__board[i][j + 1] == '+')):
                    return i, j
        return 0, 0

    def change_direction(self, direction):
        if direction == 'up' and self.__snake_direction == 'down' or direction == 'down' and self.__snake_direction == 'up':
            raise ValueError("Snake cannot turn 180 degrees!")
        if direction == 'right' and self.__snake_direction == 'left' or direction == 'left' and self.__snake_direction == 'right':
            raise ValueError("Snake cannot turn 180 degrees!")
        if direction == self.__snake_direction:
            raise ValueError("Snake is already in this direction!")
        row_head, column_head = self.snake_head()
        row_end, column_end = self.snake_end()
        if direction == 'right':
            if column_head == self.__size:
                return False
            if self.__board[row_head][column_head + 1] == '+':
                return False
            if not self.__board[row_head][column_head + 1] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head][column_head + 1] = '*'
            self.__board[row_head][column_head] = '+'

        if direction == 'left':
            if column_head == 0:
                return False
            if self.__board[row_head][column_head - 1] == '+':
                return False
            if not self.__board[row_head][column_head - 1] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head][column_head - 1] = '*'
            self.__board[row_head][column_head] = '+'

        if direction == 'up':
            if row_head == self.__size:
                return False
            if self.__board[row_head - 1][column_head] == '+':
                return False
            if not self.__board[row_head - 1][column_head] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head - 1][column_head] = '*'
            self.__board[row_head][column_head] = '+'

        if direction == 'down':
            if row_head == 0:
                return False
            if self.__board[row_head + 1][column_head] == '+':
                return False
            if not self.__board[row_head + 1][column_head] == 'a':
                self.__board[row_end][column_end] = ' '
            else:
                self.__snake_size += 1
                self.place_apples(1)
            self.__board[row_head + 1][column_head] = '*'
            self.__board[row_head][column_head] = '+'

        self.__snake_direction = direction
        return True

    def __str__(self):
        conect4_board = Texttable()
        for i in range(self.__size):
            row = self.__board[i]
            conect4_board.add_row(row)
        return conect4_board.draw()
