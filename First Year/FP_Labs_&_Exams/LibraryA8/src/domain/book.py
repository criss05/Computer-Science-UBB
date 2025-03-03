class Book:
    def __init__(self, book_id, title, author):
        self._book_id = book_id
        self._title = title
        self._author = author

    @property
    def book_id(self):
        return self._book_id

    @property
    def title(self):
        return self._title

    @property
    def author(self):
        return self._author

    @title.setter
    def title(self, new_title):
        self._title = new_title

    @author.setter
    def author(self, new_author):
        self._author = new_author

    def __eq__(self, book):
        if not isinstance(book, Book):
            return False
        return self.book_id == book.book_id

    def __str__(self):
        return f"Book ID: {self.book_id} | Title: {self.title} | Author: {self.author}"
