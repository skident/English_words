#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include "PushLabel.h"
#include <QString>

//class Controller;

class View: public QObject
{
    Q_OBJECT

private:
    QWidget* wgt_MainWindow;
    QLabel* lbl_WordsDisplay;
    PushLabel* lbl_ShowPrev;
    PushLabel* lbl_ShowNext;
//    Controller* m_pController;

public:
    View();
    ~View();

    void ShowWord(QString sWord);

private slots:
    void slotPrevClicked();
    void slotNextClicked();
};

#endif // VIEW_H
