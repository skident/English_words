/*! \brief Controller which manages words and their displaying
 *
 *  This Class connects model and view.
 */

#pragma once

#include <QObject>
#include "View.h"
#include "Model.h"
#include <QTimer>
#include <QVector>

class Controller : public QObject
{
    Q_OBJECT
private:
    View*                   m_pView;
    Model*                  m_pModel;
    QTimer*                 m_pTimer;
    unsigned int            m_nCurrIndex;
    unsigned int            m_nTimeout;
    QPair<QString, QString> m_CurrWordsPair;
    QVector<int>            m_Indexes;
    static Controller*      m_self;

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
    void ShowWord(bool bNext = true);
};


