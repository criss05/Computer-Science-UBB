from src.repository.MemoryRepository import MemoryRepository
from src.repository.BinaryRepository import BinaryRepository
from src.repository.FileRepository import FileRepository
from src.services.service import Services
from src.ui.UI import UI

# repository = MemoryRepository()
# repository = BinaryRepository()
repository = FileRepository()

services = Services(repository)
ui = UI(services)
ui.menu_application()
