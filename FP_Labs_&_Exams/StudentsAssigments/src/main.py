from src.repository import FileRepository
from src.services import Service
from src.ui import UI

repository = FileRepository("assigments.txt")
service = Service(repository)
ui = UI(service)

ui.menu_aplication()
