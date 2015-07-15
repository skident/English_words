/*! \brief Controller which manages words and their displaying
 *
 *  This Class connects model and view.
 */

#pragma once

#include <QObject>
#include "MainView.h"
#include "Model.h"
#include <QTimer>
#include <QVector>
#include <memory>

class Controller : public QObject
{
    Q_OBJECT

private:
    static Controller*      m_self;

    std::unique_ptr<MainView>               m_pView;
    std::unique_ptr<Model>                  m_pModel;
    std::unique_ptr<QTimer>                 m_pTimer;

    unsigned int            m_nCurrIndex;
    unsigned int            m_nTimeout;
    QPair<QString, QString> m_CurrWordsPair;
    QVector<int>            m_Indexes;

    void Delay(int millisecondsToWait);

    Controller();
    virtual ~Controller();

public:
    static Controller* Get()
    {
        if (!m_self)
            m_self = new Controller();
        return m_self;
    }

    void LoadData(); //filename from config
    void Start();
    void Stop();

    void GetPrevWord();
    void GetNextWord();


    void Prev();
    void Next();

public slots:
    void slotShowWord(bool bNext = true);

    void slotClose();
    void slotSettings();
    void slotAbout();

};


