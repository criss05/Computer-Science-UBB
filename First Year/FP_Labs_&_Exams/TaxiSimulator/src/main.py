from UI.UI import UI
from repository.taxi_repo import TaxiRepository
from service.taxiservice import TaxiService

taxi_ropository = TaxiRepository()
taxi_service = TaxiService(taxi_ropository)
ui = UI(taxi_service)

ui.print_menu()
ui.menu_aplication()
