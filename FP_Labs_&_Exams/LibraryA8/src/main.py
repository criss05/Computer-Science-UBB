from src.domain.validator import ValidateClient, ValidateBook, ValidateRental

from src.repository.book_repository import BookRepository
from src.repository.client_repository import ClientRepository
from src.repository.rental_repository import RentalRepository
from src.services.service_book import Service_book
from src.services.service_client import Service_client
from src.services.service_rental import RentalService
from src.ui.UI import UI


client_validation = ValidateClient()
book_validation = ValidateBook()
rental_validation = ValidateRental()

repository_book = BookRepository()
repository_client = ClientRepository()
repository_rental = RentalRepository()

service_book = Service_book(repository_book, book_validation)
service_client = Service_client(repository_client, client_validation)
service_rental = RentalService(repository_rental, repository_book, repository_client, rental_validation)

Ui = UI(service_client, service_book, service_rental)
Ui.menu_application()
