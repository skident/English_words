#pragma once

#include <string>
#include <map>

class Words
{
private:
    std::string                         m_sFileName;
    std::map<unsigned int, std::string> m_origLangMap;
    std::map<unsigned int, std::string> m_transLangMap;
    unsigned int                        m_nCurrIndex;
    unsigned int                        m_nWordsCount;
    bool                                m_isRandom;

    unsigned int GenNextIdx();

public:
    Words(bool isRandom = true);
    ~Words();

    void Reset();
    void LoadWords(std::string sFileName, char cDelimiter = '-');

    int RandInt(int low, int high);
    std::pair<std::string, std::string> GetNext();
};
