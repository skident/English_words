#include "Controller.h"

#include "AboutView.h"
#include "SettingsView.h"

#include <QDebug>
#include <chrono>
#include <future>
#include <mutex>

#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

using namespace std;


Controller* Controller::m_self = nullptr;

Controller::Controller()
    : m_nCurrIndex(0)
    , m_nTimeout(6000)
{
    m_pView.reset(new MainView());
    m_pModel.reset(new Model());
    m_pTimer.reset(new QTimer());

    m_pTimer->setInterval(m_nTimeout);
    //SIGNALS - SLOTS
    connect(m_pTimer.get(),       SIGNAL(timeout()), this, SLOT(slotShowWord()));
}

Controller::~Controller()
{
}

 //filename from config
void Controller::LoadData()
{
//    bool bRet = m_pModel->LoadData("E:\\words.txt", "-");
    bool bRet = m_pModel->LoadData("e:\\Media\\Docs\\English words\\DenisSchool.txt", "-");
    if (!bRet)
    {
        qDebug() << "Data were not loaded.";
        return;
    }

    m_Indexes.clear();
    for (int i = 0; i < m_pModel->GetWordsCount(); i++)
        m_Indexes.push_back(i);
    m_nCurrIndex = 0;
}

void Controller::Start()
{
    m_pTimer->start();
}

void Controller::Stop()
{
    m_pTimer->stop();
}

void Controller::Next()
{
    Stop();
    m_nCurrIndex++;
    if (m_nCurrIndex == m_Indexes.size())
        m_nCurrIndex = 0;
    slotShowWord(false);
    Start();
}

void Controller::Prev()
{
    Stop();
    if (m_nCurrIndex == 0)
        m_nCurrIndex = m_Indexes.size() - 1;
    else
        m_nCurrIndex--;
    slotShowWord(false);
    Start();
}

/**
 * @brief Controller::ShowWord - starts
 * @param bShowNext
 */
void Controller::slotShowWord(bool bShowNext)
{
    qDebug() << __FUNCTION__;

    if (bShowNext)
    {
        m_nCurrIndex++;
        if (m_nCurrIndex == m_Indexes.size())
            m_nCurrIndex = 0;
    }

    m_CurrWordsPair = m_pModel->getWordsPair(m_Indexes[m_nCurrIndex]);
    m_pView->ShowWord(m_CurrWordsPair.first);

    Delay(m_nTimeout/2);
    m_pView->ShowWord(m_CurrWordsPair.first + " - " + m_CurrWordsPair.second);
}


void Controller::Delay(int millisecondsToWait)
{
    qDebug() << endl << "Delay starts";
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    qDebug() << "Delay finished" << endl;
}

void Controller::slotClose()
{
    delete m_self;
}

void Controller::slotAbout()
{
    qDebug() << __FUNCTION__;
    m_pTimer->stop();
    AboutView* about = new AboutView();
//    about->show(); //maybe need make it async
//    m_pTimer->start();
}

void Controller::slotSettings()
{
    qDebug() << __FUNCTION__;
    m_pTimer->stop();
    SettingsView* settings = new SettingsView();
//    Settings settings;
//    if ( QDialog::Accepted == settings.exec() )
//    {
//        qDebug() << "New config";
//        applySettings();
//    }

//    m_pTimer->start();
}

