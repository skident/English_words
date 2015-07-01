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
#include <QPoint>

class MainView: public QObject
{
    Q_OBJECT

private:
    QWidget*    wgt_MainWindow;
    QLabel*     lbl_WordsDisplay;
    PushLabel*  lbl_ShowPrev;
    PushLabel*  lbl_ShowNext;

public:
    MainView();
    virtual ~MainView();

    void ShowWord(QString sWord);

private slots:
    void slotPrevClicked();
    void slotNextClicked();

    void slotShowContextMenu(const QPoint &pos);
};

#endif // VIEW_H
