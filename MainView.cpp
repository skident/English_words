#include "MainView.h"

#include <QDebug>
#include <QPushButton>
#include "Controller.h"

#include <QAbstractScrollArea>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QApplication>

MainView::MainView()
    : wgt_MainWindow(nullptr)
    , lbl_WordsDisplay(nullptr)
    , lbl_ShowPrev(nullptr)
    , lbl_ShowNext(nullptr)
{
    qDebug() << __FUNCTION__;

    wgt_MainWindow              = new QWidget();
    QHBoxLayout* lay_MainLayout = new QHBoxLayout();
    lbl_WordsDisplay            = new QLabel();
    lbl_ShowPrev                = new PushLabel();
    lbl_ShowNext                = new PushLabel();


    //Arrows backward and forward
    QString path = QApplication::applicationDirPath();
    qDebug() << "PATH: " << path;

    lbl_ShowPrev->setPixmap(QPixmap(path + "/icons/arrow-prev.png"));
    lbl_ShowNext->setPixmap(QPixmap(path + "/icons/arrow-next.png"));
    lbl_ShowPrev->setScaledContents(true);
    lbl_ShowNext->setScaledContents(true);
    lbl_ShowPrev->setFixedSize(QSize(30,30));
    lbl_ShowNext->setFixedSize(QSize(30,30));

    lbl_WordsDisplay->setText("Words loading...");

    lay_MainLayout->addWidget(lbl_ShowPrev);
    lay_MainLayout->addWidget(lbl_ShowNext);
    lay_MainLayout->addWidget(lbl_WordsDisplay);
    wgt_MainWindow->setLayout(lay_MainLayout);
    wgt_MainWindow->setContextMenuPolicy(Qt::CustomContextMenu);
    wgt_MainWindow->show();


    //actions
    connect(lbl_ShowPrev,       SIGNAL(clicked()),                          this, SLOT(slotPrevClicked()));
    connect(lbl_ShowNext,       SIGNAL(clicked()),                          this, SLOT(slotNextClicked()));
    connect(wgt_MainWindow,     SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotShowContextMenu(QPoint)));
}

MainView::~MainView()
{
    qDebug() << __FUNCTION__;

    delete wgt_MainWindow; //must deletes after all elements on it
}


void MainView::ShowWord(QString sWord)
{
    lbl_WordsDisplay->setText(sWord);
}

void MainView::slotPrevClicked()
{
    qDebug()<<"Prev Clicked";
    Controller::Get()->Prev();
}

void MainView::slotNextClicked()
{
    qDebug()<<"Next Clicked";
    Controller::Get()->Next();
}

void MainView::slotShowContextMenu(const QPoint &pos)
{
    qDebug() << "Show context menu";


    QPoint globalPos;  //get global coordinates
    if (sender()->inherits("QAbstractScrollArea"))
        globalPos = ((QAbstractScrollArea*)sender())->viewport()->mapToGlobal(pos);     // if query from QAbstractScrollArea
    else
        globalPos = ((QWidget*)sender())->mapToGlobal(pos);  //query from other widgets


    //create actions
    QAction* actSettings    = new QAction(QString::fromUtf8("Settings"), this);
    QAction* actAbout       = new QAction(QString::fromUtf8("About"), this);
    QAction* actExit        = new QAction(QString::fromUtf8("Exit"), this);

    //set shortcuts
    actSettings->setShortcut(Qt::ControlModifier + Qt::Key_I);
    actExit->setShortcut(Qt::ControlModifier + Qt::Key_Q);

    //build menu
    QMenu menu;
    menu.addAction(actSettings);
    menu.addSeparator();
    menu.addAction(actAbout);
    menu.addSeparator();
    menu.addAction(actExit);


    connect(actSettings,   SIGNAL(triggered()), Controller::Get(), SLOT(slotSettings()));
    connect(actAbout,      SIGNAL(triggered()), Controller::Get(), SLOT(slotAbout()));
    connect(actExit,       SIGNAL(triggered()), Controller::Get(), SLOT(slotClose()));

    menu.exec(globalPos);
}
