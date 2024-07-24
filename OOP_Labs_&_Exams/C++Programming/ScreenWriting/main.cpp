#include "ScreenWriting.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include "Repo.h"
#include "Writer.h"
#include "WriterModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo("ideas.txt", "writers.txt");
    WriterModel* model = new WriterModel(repo);

    for (auto w : repo.GetWriters()) {
        GUI* gui = new GUI{repo, w, model};
        gui->setWindowTitle(QString::fromStdString(w.GetName()));
        gui->show();
    }
    return a.exec();
}
