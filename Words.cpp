#include "Words.h"

#include <fstream>
#include <exception>
#include <QTime>

#include <iostream>

using namespace std;

//string& trim(string& str)
string trim(string str)
{
    // trim trailing spaces
    size_t endpos = str.find_last_not_of(" \t");
    if( string::npos != endpos )
    {
        str = str.substr(0, endpos+1 );
    }

    // trim leading spaces
    size_t startpos = str.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        str = str.substr( startpos );
    }

    return str;
}

Words::Words(bool isRandom)
    : m_nCurrIndex(0)
    , m_nWordsCount(0)
    , m_isRandom(isRandom)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

Words::~Words()
{
}

void Words::Reset()
{
    m_nCurrIndex = 0;
    m_nWordsCount = 0;
    m_isRandom = true;
    m_origLangMap.clear();
    m_transLangMap.clear();
    m_sFileName.clear();
}

void Words::LoadWords(string sFileName, char cDelimiter)
{
    if (sFileName.empty())
        throw invalid_argument("File name can't be empty");

    Reset();

    m_sFileName = sFileName;
    fstream in;
    string sLine;
    string sFirst, sSecond;

    m_origLangMap.clear();

//    if ( QFile::exists(m_sFileName.c_str()) == false )
//    {
//        lbl_words->setText("ERROR FILE NOT FOUND!");
//        return;
//    }

    in.open(m_sFileName.c_str(), ios::in);

    int idx = 0;
    while (getline(in, sLine))
    {
        size_t pos = sLine.find(cDelimiter);
        if ( sLine.empty() || sLine.find("Day #") != string::npos || pos == string::npos )
            continue;

        sFirst = sLine.substr(0, pos);
        sSecond = sLine.substr(pos+1);

        if (sFirst.empty() || sSecond.empty())
            continue;

        m_origLangMap.insert(pair<int, string>(idx, trim(sFirst)));
        m_transLangMap.insert(pair<int, string>(idx, trim(sSecond)));
        idx++;
    }

    m_nWordsCount = m_origLangMap.size();
//    qDebug() << "Words count " << m_nWordsCount;
}

int Words::RandInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}


unsigned int Words::GenNextIdx()
{
    if (m_isRandom)
        m_nCurrIndex = RandInt(0, m_nWordsCount-1); //0 to count of words in container
    else
        m_nCurrIndex++;

    return m_nCurrIndex;
}

pair<string, string> Words::GetNext()
{
    GenNextIdx();

    return pair<string, string>(m_origLangMap[m_nCurrIndex], m_transLangMap[m_nCurrIndex]);
}
