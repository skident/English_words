#include "WordsController.h"
#include "ui_WordsController.h"

#include <QTimer>
#include <QTime>

//#include "about.h"
#include "settings.h"
#include "config.h"
#include <QDebug>

#include <future>
#include <chrono>

#include <QHBoxLayout>
#include <QWidget>

#define SAFE_DELETE(ptr) {delete ptr; ptr = nullptr;}

using namespace std;

void delay(int millisecondsToWait)
{
    qDebug() << endl << "Delay starts";
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    qDebug() << "Delay finished" << endl;
}


WordsController::WordsController(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Words)
    , m_pLabelWords(nullptr)
    , m_pWords(nullptr)
    , m_nTimeout(0)
    , m_pTimer(nullptr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_pWords = new Words();
    m_pTimer = new QTimer(this);


    m_pLabelWords = new QLabel(this);
    m_pLabelWords->setAlignment(Qt::AlignCenter);
    m_pLabelWords->setContextMenuPolicy(Qt::CustomContextMenu); // устанавливаем специальную политику отображения меню


    m_pMainWidget = new QWidget();
    m_pMainLayout = new QHBoxLayout();
    m_pButPlay = new QToolButton(this);
    m_pButPause = new QToolButton(this);

    m_pMainLayout->addWidget(m_pButPlay);
    m_pMainLayout->addWidget(m_pButPause);
    m_pMainLayout->addWidget(m_pLabelWords);
    m_pMainWidget->setLayout(m_pMainLayout);
    setCentralWidget(m_pMainWidget);

    if (!Config::get()->load())
    {
        qDebug() << "default config used";
    }
    applySettings();

    //SIGNALS - SLOTS
    connect(m_pTimer,       SIGNAL(timeout()), this, SLOT(ShowNextWord()));
    connect(m_pButPlay,     SIGNAL(clicked()), this, SLOT(Play()));
    connect(m_pButPause,    SIGNAL(clicked()), this, SLOT(Pause()));
    connect(m_pLabelWords,  SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));     // ждем сигнала для отображения меню
}

WordsController::~WordsController()
{
    qDebug() << __FUNCTION__;

    Stop();

    SAFE_DELETE(ui)
//    SAFE_DELETE(m_pTimer)
//    SAFE_DELETE(m_pLabelWords)
//    SAFE_DELETE(m_pWords)
//    SAFE_DELETE(m_pMainWidget)
//    SAFE_DELETE(m_pMainLayout)
//    SAFE_DELETE(m_pButPlay)
//    SAFE_DELETE(m_pButPause)
}

void WordsController::Start()
{
    qDebug() << __FUNCTION__ << endl;
    m_pTimer->start();
    emit(ShowNextWord());
}

void WordsController::Stop()
{
    disconnect(m_pTimer,        SIGNAL(timeout()), this, SLOT(ShowNextWord()));
    disconnect(m_pLabelWords,   SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));     // ждем сигнала для отображения меню
}

void WordsController::exit_action()
{
    qDebug() << __PRETTY_FUNCTION__;
    close();
}

void WordsController::closeEvent(QCloseEvent * e)
{
     if ( e )
        emit(on_close_clicked());
}

void WordsController::on_close_clicked()
{
    m_pTimer->stop();
    qDebug() << __PRETTY_FUNCTION__;
    delete this;
}

void WordsController::about_action()
{
    m_pTimer->stop();
    About* about = new About();
    about->show(); //maybe need make it async
    m_pTimer->start();
}

void WordsController::settings_action()
{
    qDebug() << __FUNCTION__;
    m_pTimer->stop();
    Settings settings;
    if ( QDialog::Accepted == settings.exec() )
    {
        qDebug() << "New config";
        applySettings();
    }

    m_pTimer->start();
}

void WordsController::Play()
{
    qDebug() << __FUNCTION__;
    if (!m_pTimer->isActive())
        m_pTimer->start();
}

void WordsController::Pause()
{
    qDebug() << __FUNCTION__;
    if (m_pTimer->isActive())
        m_pTimer->stop();
}

void WordsController::ShowNextWord()
{
    qDebug() << endl << __FUNCTION__ << " starts";
    string sFirstWord = "";
    string sFullString = "";

    if (!m_pWords)
        return;
    auto pair_words = m_pWords->GetNext();
    if (pair_words.first == "" || pair_words.second == "")
        return;

    if ( Config::get()->getParam(Config::tag_words_direction).toInt() == Config::showForward )
    {
        sFirstWord = pair_words.first;
        sFullString = pair_words.first + " - " + pair_words.second;
    }
    else
    {
        sFirstWord = pair_words.second;
        sFullString = pair_words.second + " - " + pair_words.first;
    }

    if (!m_pLabelWords)
        return;
    m_pLabelWords->setText(sFirstWord.c_str());

//    delay(m_nTimeout/2);

    if (!m_pLabelWords)
        return;
    m_pLabelWords->setText(sFullString.c_str());

    qDebug() << __FUNCTION__ << " finished" << endl;
}



void WordsController::applySettings()
{
    qDebug() << "Apply Settings start";

    //form settings
    QColor  bgColor(Config::get()->getParam(Config::tag_form_bgcolor));
    QColor  fontColor(Config::get()->getParam(Config::tag_font_color));

    //words settings
    QString sFileName   = Config::get()->getParam(Config::tag_words_filename);
    qreal   nOpacity    = Config::get()->getParam(Config::tag_form_opacity).toDouble() / 100;
    m_nTimeout          = Config::get()->getParam(Config::tag_words_timeout).toInt() * 1000;

    //font settings
    int     fontSize    = Config::get()->getParam(Config::tag_font_size).toInt();
    bool    isBold      = Config::get()->getParam(Config::tag_font_bold).toInt();
    bool    isItalic    = Config::get()->getParam(Config::tag_font_italic).toInt();
    QString sFontFamily = Config::get()->getParam(Config::tag_font_family);
    QFont   font(sFontFamily, fontSize, isBold, isItalic);


    //apply settings
    m_pWords->LoadWords(sFileName.toStdString());
    setWindowOpacity(nOpacity);

    QString formStyle = "background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6)";
    m_pLabelWords->setStyleSheet(formStyle.arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()).arg(fontColor.red()).arg(fontColor.green()).arg(fontColor.blue()));
    m_pLabelWords->setFont(font);

    m_pTimer->setInterval(m_nTimeout);
}

void WordsController::mousePressEvent(QMouseEvent *event)
{
    m_mpos = event->pos();
}

bool WordsController::eventFilter(QObject* object, QEvent* event)
{
    qDebug() << __PRETTY_FUNCTION__;

    if( object == ui->centralWidget )
    {
        if ( event->type() == QEvent::Enter )
        {
            m_pLabelWords->setStyleSheet("color:blue; font-size:12pt");
        }

        if( event ->type() == QEvent::Leave )
        {
            m_pLabelWords->setStyleSheet("color:black; font-size:12pt");
        }
    }
    return false;
}

void WordsController::mouseMoveEvent(QMouseEvent *event)
{
    if (this->rect().contains(event->pos()))
    {
        qDebug() << "SHOW";
        m_pButPlay->show();
        m_pButPause->show();
    }
    else
    {
        qDebug() << "HIDE";
        m_pButPlay->hide();
        m_pButPause->hide();
    }

//    if (event->buttons() && Qt::LeftButton)
//    {
//        QPoint diff = event->pos() - m_mpos;
//        QPoint newpos = this->pos() + diff;

//        this->move(newpos);
//    }


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
    if (e == nullptr)
        return;
}

