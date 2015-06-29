#include "View.h"

#include <QDebug>
#include <QPushButton>
#include "Controller.h"

View::View()
    : wgt_MainWindow(nullptr)
    , lbl_WordsDisplay(nullptr)
    , lbl_ShowPrev(nullptr)
    , lbl_ShowNext(nullptr)
//    , m_pController(nullptr)
{
    qDebug() << __FUNCTION__;


//    Controller* m_pController = Controller::Get();

    wgt_MainWindow = new QWidget();
    QHBoxLayout* lay_MainLayout = new QHBoxLayout();
    lbl_WordsDisplay = new QLabel();
    lbl_ShowPrev = new PushLabel();
    lbl_ShowNext = new PushLabel();

    //Arrows backward and forward
//    lbl_ShowPrev->setPixmap(QPixmap(QString::fromUtf8(":/icons/arrow-prev.png")));
//    lbl_ShowNext->setPixmap(QPixmap(QString::fromUtf8(":/icons/arrow-next.png")));
    lbl_ShowPrev->setPixmap(QPixmap("E:\\Dev\\Projects\\Qt\\English_words\\icons\\arrow-prev.png"));
    lbl_ShowNext->setPixmap(QPixmap("E:\\Dev\\Projects\\Qt\\English_words\\icons\\arrow-next.png"));
    lbl_ShowPrev->setScaledContents(true);
    lbl_ShowNext->setScaledContents(true);
    lbl_ShowPrev->setFixedSize(QSize(30,30));
    lbl_ShowNext->setFixedSize(QSize(30,30));

    lbl_WordsDisplay->setText("Label for tests");


    lay_MainLayout->addWidget(lbl_ShowPrev);
    lay_MainLayout->addWidget(lbl_ShowNext);
    lay_MainLayout->addWidget(lbl_WordsDisplay);
    wgt_MainWindow->setLayout(lay_MainLayout);
    wgt_MainWindow->show();




    //actions
    connect(lbl_ShowPrev, SIGNAL(clicked()), this, SLOT(slotPrevClicked()));
    connect(lbl_ShowNext, SIGNAL(clicked()), this, SLOT(slotNextClicked()));
//    connect(wgt_MainWindow, SIGNAL())
}

View::~View()
{
    qDebug() << __FUNCTION__;

    delete wgt_MainWindow; //must deletes after all elements on it
}


void View::ShowWord(QString sWord)
{
    lbl_WordsDisplay->setText(sWord);
}

void View::slotPrevClicked()
{
    qDebug()<<"Prev Clicked";
//    if (m_pController)
        Controller::Get()->Prev();
    //Said controller to get previous word!
//    m_pController->Controller();
//    lbl_WordsDisplay->setText("12345678900987654321");
}

void View::slotNextClicked()
{
//    lbl_WordsDisplay->setText("1234567890098765432112345678900987654321");
    qDebug()<<"Next Clicked";
//    if (m_pController)
        Controller::Get()->Next();
    //Said controller to get next word!
}
