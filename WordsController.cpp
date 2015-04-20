#include "WordsController.h"
#include "ui_words.h"

#include <fstream>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QWidget>

#include "about.h"
#include "settings.h"
#include "config.h"

#include <QDebug>

using namespace std;

WordsController* WordsController::m_self = NULL;

WordsController::WordsController(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Words)
    , m_ptrWords(nullptr)
    , m_timer(nullptr)
    , m_trIcon(nullptr)
    , m_lbl_words(nullptr)
{
    ui->setupUi(this);

    m_ptrWords = new Words();
    m_timer = new QTimer(this);

    m_trIcon = new QSystemTrayIcon();  //инициализируем объект
    m_trIcon->setIcon(QIcon(":/img/icon.png"));  //устанавливаем иконку
    m_trIcon->show();  //отображаем объект

    m_lbl_words = new QLabel;
    m_lbl_words->setAlignment(Qt::AlignCenter);
    m_lbl_words->setContextMenuPolicy(Qt::CustomContextMenu); // устанавливаем специальную политику отображения меню
    setCentralWidget(m_lbl_words);

    applySettings();

    m_timer->start(Config::get()->getTimeout());

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    //SIGNALS - SLOTS
    connect(m_trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(ShowNextWord()));
    connect(m_lbl_words, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));     // ждем сигнала для отображения меню
}

WordsController::~WordsController()
{
    delete ui;
    delete m_self;
    delete m_timer;
    delete m_trIcon;
    delete m_lbl_words;
    delete m_ptrWords;
}

WordsController* WordsController::Get()
{
    if ( !m_self )
        m_self = new WordsController();
    return m_self;
}

void WordsController::Load()
{
    m_ptrWords->LoadWords(Config::get()->getFileName());
    emit(ShowNextWord());
}

void WordsController::showHide(QSystemTrayIcon::ActivationReason r)
{
    if ( r == QSystemTrayIcon::Trigger )  //если нажато левой кнопкой продолжаем
    {
        if (!this->isVisible())  //если окно было не видимо - отображаем его
            this->show();
        else
            this->hide();  //иначе скрываем
    }
}

void WordsController::exit_action()
{
    close();
}

void WordsController::about_action()
{
    m_timer->stop();
    About* about = new About();
    about->show();
    m_timer->start();
}

void WordsController::settings_action()
{
    m_timer->stop();
    Settings::get()->show();
}

void WordsController::ShowNextWord()
{
    string sFirstWord = "";
    string sFullString = "";

    auto pair_words = m_ptrWords->GetNext();
//    qDebug() << pair_words.first.c_str() << pair_words.second.c_str();

    if ( Config::get()->getShowType() == Config::showForward )
    {
        sFirstWord = pair_words.first;
        sFullString = pair_words.first + " - " + pair_words.second;
    }
    else
    {
        sFirstWord = pair_words.second;
        sFullString = pair_words.second + " - " + pair_words.first;
    }

//    qDebug() << sFullString.c_str();

    m_lbl_words->setText(sFirstWord.c_str());

    delay(Config::get()->getTimeout()/2);
    m_lbl_words->setText(sFullString.c_str());
}

void WordsController::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void WordsController::applySettings()
{
    qDebug() << "Apply Settings start";

    Config* pCfg            = Config::get();
    QColor bgColor          = pCfg->getBgColor();
    QColor fontColor        = pCfg->getFontColor();
    QFont font              = pCfg->getFont();
    qreal nOpacity          = pCfg->getOpacity();

    setWindowOpacity(nOpacity);

    QString formStyle = "background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6)";
    m_lbl_words->setStyleSheet(formStyle.arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()).arg(fontColor.red()).arg(fontColor.green()).arg(fontColor.blue()));
    m_lbl_words->setFont(font);

    m_timer->start(pCfg->getTimeout());

}


void WordsController::mousePressEvent(QMouseEvent *event){
    m_mpos = event->pos();
}

void WordsController::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - m_mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void WordsController::showContextMenu(const QPoint &pos)
{
    // получаем глобальные координаты
    QPoint globalPos;
    // если запрос от QAbstractScrollArea
    if (sender()->inherits("QAbstractScrollArea"))
        globalPos = ((QAbstractScrollArea*)sender())->viewport()->mapToGlobal(pos);
    // если от других виджетов
    else
        globalPos = ((QWidget*)sender())->mapToGlobal(pos);

    // Создаем меню
    QMenu menu;

    QAction *Settings = new QAction(QString::fromUtf8("Настройки"), this);
    menu.addAction(Settings);
    menu.addSeparator();  // добавляем разделитель

    QAction *About = new QAction(QString::fromUtf8("О программе"), this);
    menu.addAction(About);
    menu.addSeparator();  // добавляем разделитель

    QAction *Exit = new QAction(QString::fromUtf8("Выход"), this);
    menu.addAction(Exit);

    connect(Settings,   SIGNAL(triggered()), this, SLOT(settings_action()));
    connect(About,      SIGNAL(triggered()), this, SLOT(about_action()));
    connect(Exit,       SIGNAL(triggered()), this, SLOT(exit_action()));

    menu.exec(globalPos);
}

void WordsController::mouseDoubleClickEvent(QMouseEvent * e)
{
//qDebug() << "double click";
//    emit(onFormDbClick());
//    setWindowFlags();
//    if ( isTitle )
//        setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
//    else
//        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

//    Qt::WindowFlags flags = windowFlags();
//    qDebug() << flags;

//    if ( flags & Qt::FramelessWindowHint )
//    {
//        flags ^= Qt::FramelessWindowHint;
//        qDebug() << flags;

//        setWindowFlags(flags);
//    }

}
