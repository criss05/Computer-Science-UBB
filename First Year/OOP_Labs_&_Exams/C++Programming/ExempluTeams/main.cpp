#include "ExempluTeams.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repo repo("users.txt", "issues.txt");

    Service service(repo);

    for (auto u : repo.GetUser()) {
        GUI* gui = new GUI(service, u);
        gui->setWindowTitle(QString::fromStdString(u.GetName() + "-" + u.GetType()));
        gui->show();
    }

    return a.exec();
}
