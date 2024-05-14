import configparser
import tkinter as tk

from UI import UI
from gui import ConnectFourGUI


def console_interface():
    console = UI()
    console.start_game()


def graphical_interface():
    root = tk.Tk()
    ConnectFourGUI(root)
    root.mainloop()


def choosing_interface():
    configuration = configparser.ConfigParser()
    configuration.read("settings.properties")
    interface = configuration.get("Settings", "interface", fallback='ui')
    if interface.lower() == 'graphical':
        graphical_interface()
    elif interface.lower() == 'console':
        console_interface()


if __name__ == '__main__':
    choosing_interface()
