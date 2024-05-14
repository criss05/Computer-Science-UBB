from repository import FileRepo
from service import TaxiService
from ui import UI

repository = FileRepo("taxis.txt")
service = TaxiService(repository)
ui = UI(service)

ui.print_menu()
ui.menu_aplication()
