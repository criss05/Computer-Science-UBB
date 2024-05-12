class Expenses:
    def __init__(self, day, amount_of_money, type_expenses):
        self.__day = day
        self.__amount_of_money = amount_of_money
        self.__type_expenses = type_expenses

    @property
    def day(self):
        return self.__day

    @property
    def amount_of_money(self):
        return self.__amount_of_money

    @property
    def type_expenses(self):
        return self.__type_expenses

    def __eq__(self, other):
        if not isinstance(other, Expenses):
            return False
        return self.day == other.day and self.type_expenses == other.type_expenses

    def __str__(self):
        return f"Day: {self.day} | Amount: {self.amount_of_money} | Type: {self.type_expenses}"
