import configparser

from src.UI import UI
from src.board import Board

configuration = configparser.ConfigParser()
configuration.read("settings.properties")
size = configuration.get("Settings", "size")
number_apples = configuration.get("Settings", "number_apples")

board = Board(int(size))
ui = UI(board, int(number_apples))

ui.start_game()
