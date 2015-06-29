#include "Model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <fstream>
#include <string>

using namespace std;

Model::Model()
{
    this->ResetData();
}

Model::~Model()
{

}

void Model::ResetData()
{
    m_OrigWords.clear();
    m_TransWords.clear();
    m_nWordsCount = 0;
}

bool Model::LoadData(QString sFileName, QString sDelimiter)
{
    if (sFileName.isEmpty())
        throw invalid_argument("File name can't be empty");

    ResetData();

    string sLine    = "";
    string sFirst   = "";
    string sSecond  = "";

    fstream in(sFileName.toStdString().c_str(), ios::in);

    int idx = 0;
    while (getline(in, sLine))
    {
        size_t pos = sLine.find(sDelimiter.toStdString());
        if ( sLine.empty() || sLine.find("Day #") != string::npos || pos == string::npos )
            continue;

        sFirst = sLine.substr(0, pos);
        sSecond = sLine.substr(pos+1);

        if (sFirst.empty() || sSecond.empty())
            continue;

        m_OrigWords[idx] = QString::fromStdString(sFirst);
        m_TransWords[idx] = QString::fromStdString(sSecond);
        idx++;
    }

    m_nWordsCount = m_OrigWords.size();
    qDebug() << "Words count " << m_nWordsCount;

    if (m_nWordsCount == 0)
        return false;
    return true;
}


//bool Model::LoadData(QString sFileName, QString sDelimiter)
//{
//    if (sFileName.isEmpty())
//        return false;
////        throw invalid_argument("File name can't be empty");

////    if (QFile::exists(sFileName.c_str()) == false)
////    {
//////        lbl_words->setText("ERROR FILE NOT FOUND!");
////        return;
////    }

//    this->ResetData();


//    QFile inputFile(sFileName);
//    if (inputFile.open(QIODevice::ReadOnly))
//    {
//        QString sFirst = "";
//        QString sSecond = "";
//        QString sLine = "";
//        QTextStream in(&inputFile);
//        unsigned int idx = 0;
//        while (!in.atEnd())
//        {
//            sLine = in.readLine();

//            if (sLine.isEmpty() || !sLine.contains(sDelimiter))
//                continue;

//            unsigned long pos = sLine.indexOf(sDelimiter);
//            sFirst = sLine.left(pos);
//            sSecond = sLine.right(pos+1);
//            //          sFirst = sLine.substr(0, pos);
//            //          sSecond = sLine.substr(pos+1);

//            if (sFirst.isEmpty() || sSecond.isEmpty())
//              continue;

//            m_OrigWords.insert(idx, sFirst);
//            m_TransWords.insert(idx, sSecond);
//            idx++;
//        }
//        inputFile.close();
//    }

//    m_nWordsCount = m_OrigWords.size();
//    qDebug() << "Words count " << m_nWordsCount;

//    if (m_nWordsCount == 0)
//        return false;
//    return true;
//}

unsigned int Model::GetWordsCount() const
{
    return m_nWordsCount;
}

QString Model::GetWord(unsigned int nIndex, WordType type)
{
    QString sWord = "";
    if (nIndex < GetWordsCount())
    {
        if (type == wordOrig)
            sWord = m_OrigWords[nIndex];
        else
            sWord = m_TransWords[nIndex];
    }
    qDebug() << "GetWord: " << sWord;
    return sWord;
}


QPair<QString, QString> Model::getWordsPair(unsigned int nIndex)
{
    return QPair<QString, QString>(GetWord(nIndex, wordOrig), GetWord(nIndex, wordTrans));
}

