from repository.bus_repo import BusFileRepo
from repository.routes_repo import RouteFileRepo
from service.service import Service
from ui import UI

bus_repo = BusFileRepo("buses.txt")
routes_repo = RouteFileRepo("bus_routes.txt")

service = Service(bus_repo, routes_repo)

ui = UI(service)

ui.print_menu()
ui.menu_aplication()
