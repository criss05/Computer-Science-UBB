#include "DeliverNow.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include"Service.h"
#include "Repo.h"
#include "CourierCompanyWindow.h"
#include "Map.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo("couriers.txt", "packages.txt");
    Service service(repo);

    for (auto c : repo.GetCouriers()) {
        GUI* gui = new GUI(service, c);
        gui->setWindowTitle(QString::fromStdString(c.GetName()));
        gui->show();
    }

    CourierCompanyWindow company(service);
    company.show();

    Map map(service);
    map.show();
    return a.exec();
}
