#include "WordsController.h"
#include <QApplication>

//#include "view.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    Controller c;
//    c.LoadData();
//    c.Start();

    Controller* c = Controller::Get();
    c->LoadData();
    c->Start();


//    WordsController w;
//    w.setWindowFlags(Qt::Window |  Qt::WindowStaysOnTopHint);

//    w.show();
//    w.Start();

    return a.exec();
}
