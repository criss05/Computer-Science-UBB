class UI:
    def __init__(self, board, number_of_apples):
        self.__snake_board = board
        self.__number_of_apples = number_of_apples

    def start_game(self):
        self.__snake_board.place_apples(self.__number_of_apples)
        while True:
            try:
                print(self.__snake_board)
                command = input("Command:")
                if 'move' in command:
                    if ' ' in command:
                        move, parameters = command.strip().split(" ")
                    else:
                        parameters = '1'
                    game_over = self.__snake_board.make_move(int(parameters))
                    if not game_over:
                         print('You lose!')
                         break
                elif 'up' in command or 'down' in command or 'left' in command or 'right' in command:
                    game_over = self.__snake_board.change_direction(command)
                    if not game_over:
                        print('you lose')
                        break
                else:
                    print("Invalid input!")

            except ValueError as error:
                print(error)