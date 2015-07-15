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
#include <QMainWindow>

class MainView: public QMainWindow
{
    Q_OBJECT

private:
    QWidget*    wgt_MainWindow;
    QLabel*     lbl_WordsDisplay;
    PushLabel*  lbl_ShowPrev;
    PushLabel*  lbl_ShowNext;
    QPoint      mpos;

public:
    MainView();
    virtual ~MainView();

    void ShowWord(QString sWord);


    //Windows move by drag and drop
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void slotPrevClicked();
    void slotNextClicked();

    void slotShowContextMenu(const QPoint &pos);
};

#endif // VIEW_H
