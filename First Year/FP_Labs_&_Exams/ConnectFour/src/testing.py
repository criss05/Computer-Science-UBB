from unittest import TestCase

from board import Board
from player import HumanPlayer, ComputerPlayer


class Testing(TestCase):
    def setUp(self):
        self.__board = Board()
        self.__human_player = HumanPlayer('O', self.__board)
        self.__computer_player = ComputerPlayer('X', self.__board)

    def test_human_make_move(self):
        self.__human_player.make_move('1')
        self.__human_player.make_move('2')
        self.__human_player.make_move('2')
        self.assertEqual(self.__board.place(self.__board.row_size - 1, 0), 'O')
        self.assertEqual(self.__board.place(self.__board.row_size - 1, 1), 'O')
        self.assertEqual(self.__board.place(self.__board.row_size - 2, 1), 'O')

    def test_winning_checking(self):
        # win on row
        self.__human_player.make_move('1')
        self.__human_player.make_move('2')
        self.__human_player.make_move('3')
        self.__human_player.make_move('4')
        self.assertEqual(self.__board.check_winning('O'), True)
        self.__board.undo_move(self.__board.row_size - 1, 0, 'O')
        self.__board.undo_move(self.__board.row_size - 1, 1, 'O')
        self.__board.undo_move(self.__board.row_size - 1, 2, 'O')
        self.__board.undo_move(self.__board.row_size - 1, 3, 'O')

        # win on column
        self.__human_player.make_move('1')
        self.__human_player.make_move('1')
        self.__human_player.make_move('1')
        self.__human_player.make_move('1')
        self.assertEqual(self.__board.check_winning('O'), True)
        self.__board.undo_move(self.__board.row_size - 1, 0, 'O')
        self.__board.undo_move(self.__board.row_size - 2, 0, 'O')
        self.__board.undo_move(self.__board.row_size - 3, 0, 'O')
        self.__board.undo_move(self.__board.row_size - 4, 0, 'O')

        # win on principal diagonal
        self.__board.make_move(0, 'O')
        self.__board.make_move(1, 'X')
        self.__board.make_move(1, 'O')
        self.__board.make_move(2, 'X')
        self.__board.make_move(2, 'X')
        self.__board.make_move(2, 'O')
        self.__board.make_move(3, 'X')
        self.__board.make_move(3, 'X')
        self.__board.make_move(3, 'X')
        self.__board.make_move(3, 'O')
        self.assertEqual(self.__board.check_winning('O'), True)
        self.__board.undo_move(self.__board.row_size - 1, 0, 'O')
        self.__board.undo_move(self.__board.row_size - 1, 1, 'X')
        self.__board.undo_move(self.__board.row_size - 1, 2, 'X')
        self.__board.undo_move(self.__board.row_size - 1, 3, 'X')
        self.__board.undo_move(self.__board.row_size - 2, 1, 'O')
        self.__board.undo_move(self.__board.row_size - 2, 2, 'X')
        self.__board.undo_move(self.__board.row_size - 2, 3, 'X')
        self.__board.undo_move(self.__board.row_size - 3, 2, 'O')
        self.__board.undo_move(self.__board.row_size - 3, 3, 'X')
        self.__board.undo_move(self.__board.row_size - 4, 3, 'O')

        # win on secondary diagonal
        self.__board.make_move(3, 'O')
        self.__board.make_move(2, 'X')
        self.__board.make_move(2, 'O')
        self.__board.make_move(1, 'X')
        self.__board.make_move(1, 'X')
        self.__board.make_move(1, 'O')
        self.__board.make_move(0, 'X')
        self.__board.make_move(0, 'X')
        self.__board.make_move(0, 'X')
        self.__board.make_move(0, 'O')
        self.assertEqual(self.__board.check_winning('O'), True)
        self.__board.undo_move(self.__board.row_size - 1, 3, 'O')
        self.__board.undo_move(self.__board.row_size - 1, 2, 'X')
        self.__board.undo_move(self.__board.row_size - 1, 1, 'X')
        self.__board.undo_move(self.__board.row_size - 1, 0, 'X')
        self.__board.undo_move(self.__board.row_size - 2, 2, 'O')
        self.__board.undo_move(self.__board.row_size - 2, 1, 'X')
        self.__board.undo_move(self.__board.row_size - 2, 0, 'X')
        self.__board.undo_move(self.__board.row_size - 3, 1, 'O')
        self.__board.undo_move(self.__board.row_size - 3, 0, 'X')
        self.__board.undo_move(self.__board.row_size - 4, 0, 'O')

    def test_board_full(self):
        for i in range(self.__board.column_size):
            for j in range(self.__board.row_size):
                self.__human_player.make_move(str(i + 1))
        self.assertEqual(self.__board.check_board_full(), True)

    def test_computer_win_move(self):
        self.__board.make_move(0, 'X')
        self.__board.make_move(1, 'X')
        self.__board.make_move(3, 'X')
        self.__computer_player.make_move()
        self.assertEqual(self.__board.place(self.__board.row_size-1, 2), 'X')

    def test_computer_block_move(self):
        self.__board.make_move(0, 'O')
        self.__board.make_move(1, 'O')
        self.__board.make_move(3, 'O')
        self.__computer_player.make_move()
        self.assertEqual(self.__board.place(self.__board.row_size - 1, 2), 'X')
