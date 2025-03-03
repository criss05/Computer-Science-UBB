import tkinter as tk
from board import Board
from player import HumanPlayer, ComputerPlayer


class ConnectFourGUI:
    def __init__(self, root_):
        self.__root = root_
        self.__root.title("Connect Four")
        self.__human_player_symbol = 'O'
        self.__computer_player_symbol = 'X'
        self.__board = Board()
        self.__human_player = HumanPlayer(self.__human_player_symbol, self.__board)
        self.__computer_player = ComputerPlayer(self.__computer_player_symbol, self.__board)
        self.__canvas = tk.Canvas(self.__root, width=80 * self.__board.column_size, height=80 * self.__board.row_size)
        self.__buttons = []
        self.__game_over = False
        self.__restart_button = tk.Button(self.__root, text="Restart Game", command=self.restart_game)
        self.__restart_button.grid(row=self.__board.row_size + 1, columnspan=self.__board.column_size)
        self.create_gui()

    def create_gui(self):

        self.__canvas.grid(row=0, column=0, columnspan=self.__board.column_size)

        for column in range(self.__board.column_size):
            button = tk.Button(self.__root, text=str(column + 1), command=lambda c=column: self.make_move(c),
                               font=("Helvetica", 20, "bold"))
            button.grid(row=1, column=column)
            self.__buttons.append(button)

    def make_move(self, column):
        if self.__game_over:
            return
        try:
            self.__human_player.make_move(str(column + 1))
            self.update_gui()
            if self.__board.check_winning(self.__human_player_symbol):
                self.show_winner_message("Human Player")
            elif self.__board.check_board_full():
                self.show_draw_message()
            else:
                self.__computer_player.make_move()
                self.update_gui()
                if self.__board.check_winning(self.__computer_player_symbol):
                    self.show_winner_message("Computer Player")
                elif self.__board.check_board_full():
                    self.show_draw_message()
        except Exception as error:
            print(error)

    def update_gui(self):
        self.__canvas.delete("all")
        human_player_symbol = 'O'
        computer_player_symbol = 'X'
        cell_size = 80
        for row in range(self.__board.row_size):
            for column in range(self.__board.column_size):
                value = self.__board.place(row, column)
                x1, y1 = column * cell_size, row * cell_size
                x2, y2 = x1 + cell_size, y1 + cell_size

                self.__canvas.create_rectangle(x1, y1, x2, y2, outline="black", fill="white")

                if value == human_player_symbol:
                    self.__canvas.create_oval(x1 + 5, y1 + 5, x2 - 5, y2 - 5, outline="black", fill="red")
                elif value == computer_player_symbol:
                    self.__canvas.create_oval(x1 + 5, y1 + 5, x2 - 5, y2 - 5, outline="black", fill="blue")

    def show_winner_message(self, winner):
        self.show_message(f"{winner} has won!")
        self.__game_over = True

    def show_draw_message(self):
        self.show_message("It's a draw!")

    def show_message(self, message):
        box_width = 300
        box_height = 50
        x = (self.__board.column_size * 40) - (box_width / 2)
        y = (self.__board.row_size * 40) - (box_height / 2)

        self.__canvas.create_rectangle(x, y, x + box_width, y + box_height, outline="black", fill="white")
        self.__canvas.create_text((x + box_width / 2, y + box_height / 2), text=message, font=("Helvetica", 16))

    def restart_game(self):
        self.__game_over = False
        self.__board = Board()
        self.__human_player = HumanPlayer(self.__human_player_symbol, self.__board)
        self.__computer_player = ComputerPlayer(self.__computer_player_symbol, self.__board)
        self.__canvas.delete("all")
        self.create_gui()
