import configparser

from src.domain.validator import ValidateClient, ValidateBook, ValidateRental

from src.repository.book_repository import BookRepository, BookBinaryRepository, BookTextFileRepository
from src.repository.client_repository import ClientRepository, ClientBinaryRepository, ClientTextFileRepository
from src.repository.rental_repository import RentalRepository, RentalBinaryRepository, RentalTextFileRepository
from src.services.service_book import Service_book
from src.services.service_client import Service_client
from src.services.service_rental import RentalService
from src.services.undo_service import UndoService
from src.ui.UI import UI


config = configparser.ConfigParser()
config.read('settings.properties')

client_repository_type = config.get('RepositorySettings', 'client_repository_type')
book_repository_type = config.get('RepositorySettings', 'book_repository_type')
rental_repository_type = config.get('RepositorySettings', 'rental_repository_type')

client_file_location = config.get('FileLocations', 'client_file_location')
book_file_location = config.get('FileLocations', 'book_file_location')
rental_file_location = config.get('FileLocations', 'rental_file_location')

if client_repository_type == 'memory':
    client_repository = ClientRepository()
elif client_repository_type == 'text_file':
    client_repository = ClientTextFileRepository(client_file_location)
elif client_repository_type == 'binary_file':
    client_repository = ClientBinaryRepository(client_file_location)
else:
    raise ValueError("Invalid client repository type specified in settings")

if book_repository_type == 'memory':
    book_repository = BookRepository()
elif book_repository_type == 'text_file':
    book_repository = BookTextFileRepository(book_file_location)
elif book_repository_type == 'binary_file':
    book_repository = BookBinaryRepository(book_file_location)
else:
    raise ValueError("Invalid book repository type specified in settings")

if rental_repository_type == 'memory':
    rental_repository = RentalRepository()
elif rental_repository_type == 'text_file':
    rental_repository = RentalTextFileRepository(rental_file_location)
elif rental_repository_type == 'binary_file':
    rental_repository = RentalBinaryRepository(rental_file_location)
else:
    raise ValueError("Invalid rental repository type specified in settings")


client_validation = ValidateClient()
book_validation = ValidateBook()
rental_validation = ValidateRental()

undo_service = UndoService()

service_book = Service_book(book_repository, book_validation, undo_service)
service_client = Service_client(client_repository, client_validation, undo_service)
service_rental = RentalService(rental_repository, book_repository, client_repository, rental_validation)

Ui = UI(service_client, service_book, service_rental, undo_service)
Ui.menu_application()
