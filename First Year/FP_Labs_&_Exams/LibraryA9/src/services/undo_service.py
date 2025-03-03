class Command:
    def __init__(self, operation_to_undo, *parameters):
        self._operation = operation_to_undo
        self._operation_parameters = parameters

    def execute(self):
        self._operation(*self._operation_parameters)

    def __str__(self):
        return "Operation:" + str(self._operation) + " with parameters: " + str(self._operation_parameters)


class Operation:
    def __init__(self, undo_action: Command, redo_action: Command):
        self.__undo_action = undo_action
        self.__redo_action = redo_action

    def undo(self):
        self.__undo_action.execute()

    def redo(self):
        self.__redo_action.execute()

    def __str__(self):
        return "Operation:" + str(self.__undo_action) + " & " + str(self.__redo_action)


class UndoRedoException(Exception):
    pass


class UndoService:
    def __init__(self):
        self._undo_stack = []
        self._redo_stack = []
        self._is_undoredo_operation = False
        self._can_redo = False

    def record_for_undo(self, operation: Operation):
        if self._is_undoredo_operation:
            return
        if not self._can_redo:
            self._redo_stack = []
        self._undo_stack.append(operation)
        self._can_redo = False

    def undo(self):
        print('Trying to undo..')
        if len(self._undo_stack) == 0:
            raise UndoRedoException("No more undoes!")
        self._is_undoredo_operation = True
        operation = self._undo_stack.pop()
        operation.undo()
        self._redo_stack.append(operation)
        self._is_undoredo_operation = False
        self._can_redo = True

    def redo(self):
        print('Trying to redo...')
        if len(self._redo_stack) == 0 or not self._can_redo:
            raise UndoRedoException("No more redoes!")
        self._is_undoredo_operation = True
        operation = self._redo_stack.pop()
        operation.redo()
        self._undo_stack.append(operation)
        self._is_undoredo_operation = False

    def __str__(self):
        print('Undoes and redoes:')

        operation_message = 'UNDO stack\n'
        for number_operations, operation in enumerate(self._undo_stack):
            operation_message += str(number_operations) + " "
            operation_message += str(operation)
            operation_message += '\n'
        operation_message += 'REDO stack\n'

        for number_operations, operation in enumerate(self._redo_stack):
            operation_message += str(number_operations) + " "
            operation_message += str(operation)
            operation_message += '\n'
        return operation_message
