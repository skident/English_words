/*! \brief Does all operations with data (words)
 *
 *  Loads words from file, prepare it and put to internal storage
 *  Provides methods for controller.
 *  Controller decides when model must loads data and can get all
 *  data by special methods
 */

#pragma once

#include <QMap>
#include <QString>
#include <QPair>

class Model
{
private:
    enum WordType
    {
        wordOrig,
        wordTrans
    };

    QMap<unsigned int, QString> m_OrigWords;
    QMap<unsigned int, QString> m_TransWords;
    unsigned int m_nWordsCount;

    void ResetData();
    QString GetWord(unsigned int nIndex, WordType type);

public:
    Model();
    ~Model();

    bool LoadData(QString sFileName, QString sDelimiter);
    unsigned int GetWordsCount() const;
    QPair<QString, QString> getWordsPair(unsigned int nIndex);


};

