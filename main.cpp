#include "WordsController.h"
#include <QApplication>
#include "Words.h"
#include "WordsController.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WordsController* w = WordsController::Get();
    w->setWindowFlags(Qt::Window |  Qt::WindowStaysOnTopHint);
    w->show();
    w->Load();

//    Words words;
//    words.LoadWords("D:\\words.txt");
//    words.GetNext();

    return a.exec();
}
