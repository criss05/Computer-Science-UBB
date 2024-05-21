#include "a8-9-solution.h"
#include <QtWidgets/QApplication>
#include "ClientRepository.h"
#include "EmployeesRepository.h"
#include "Service.h"
#include "GUI.h"
#include "ClientRepoType.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    

    FileEmployeesRepository* employee_repo = new FileEmployeesRepository("pets.txt");
    ClientRepositoryBase* client_repo = nullptr;

    ClientRepoType repoDialog;
    QObject::connect(&repoDialog, &ClientRepoType::Format_Chosen, [&](const QString& format) {
        if (format == "CSV")
            client_repo = new ClientRepositoryCSV("adoption_list.csv");
        else if (format == "HTML")
            client_repo = new ClientRepositoryHTML("adoption_list.html");
        });
    repoDialog.setWindowIcon(QIcon("format.png"));

    repoDialog.exec();

    Service service{ client_repo, employee_repo };
    GUI gui{ service };
    gui.show();
    return a.exec();
}


