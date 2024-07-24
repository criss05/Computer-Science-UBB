#include "StarCatalogue.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include "Repo.h"
#include "Service.h"
#include "MyModel.h"
#include <QSortFilterProxyModel>
#include "FilterModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repo repo{ "stars.txt", "astronomers.txt" };
    Service service{ repo };

    Model model(service);

    for (auto a : repo.GetAstronomers()) {
        FilterModel* filter_model = new FilterModel(model, a.GetConstellation());
        filter_model->setSourceModel(&model);
        GUI* gui = new GUI{ service, filter_model , a };
        gui->setWindowTitle(QString::fromStdString(a.GetName()));
        gui->show();
    }

    return a.exec();
}
