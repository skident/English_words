#include "Controller.h"

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
    : m_pView(nullptr)
    , m_pModel(nullptr)
    , m_pTimer(nullptr)
    , m_nCurrIndex(0)
    , m_nTimeout(6000)
{
    m_pView  = new View();
    m_pModel = new Model();
    m_pTimer = new QTimer();

    m_pTimer->setInterval(m_nTimeout);
    //SIGNALS - SLOTS
    connect(m_pTimer,       SIGNAL(timeout()), this, SLOT(ShowWord()));
}

Controller::~Controller()
{
    delete m_pView;
    delete m_pModel;
}

 //filename from config
void Controller::LoadData()
{
    bool bRet = m_pModel->LoadData("E:\\words.txt", "-");
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
    ShowWord(false);
    Start();
}

void Controller::Prev()
{
    Stop();
    if (m_nCurrIndex == 0)
        m_nCurrIndex = m_Indexes.size() - 1;
    else
        m_nCurrIndex--;
    ShowWord(false);
    Start();
}

/**
 * @brief Controller::ShowWord - starts
 * @param bRandom
 */
void Controller::ShowWord(bool bNext)
{
    qDebug() << "Start Show";
//    if (bRandom)
//        m_nCurrIndex = qrand() % m_pModel->GetWordsCount();
//    else
//        m_nCurrIndex++;

    if (bNext)
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
