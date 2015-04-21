#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QFont>
#include <QFile>
#include <string>
#include <QString>

class Config
{
public:
    enum eShowDirection
    {
        showForward,
        showBackward
    };


private:
    static Config*  m_self;

    bool            m_bNewSettings;
    eShowDirection       m_showType;
    unsigned char   m_nOpacity;
    unsigned int    m_nTimeout;
    QFont           m_font;
    QColor          m_bgColor;
    QColor          m_textColor;
    std::string     m_sFileName;

    Config();
    ~Config() { delete m_self; }

    void setParam(const QStringRef sName, const QString sValue);


public:


    static Config* get()
    {
        if ( !m_self )
            m_self = new Config();
        return m_self;
    }

//    bool            bNewSettings;
    inline void setDirection (eShowDirection __bType)         { m_showType = __bType; }
    inline void setOpacity  (qreal __fOpacity)          { m_nOpacity = __fOpacity; }
    inline void setTimeout  (unsigned char __ucTimeout) { m_nTimeout = __ucTimeout * 1000; }
    inline void setFont     (QFont __fontType)          { m_font = __fontType; }
    inline void setBgColor  (QColor __bgColor)          { m_bgColor = __bgColor; }
    inline void setFontColor(QColor __fontColor)        { m_textColor = __fontColor; }
    inline void setFileName (std::string __sFileName)   { m_sFileName = __sFileName; }


    inline eShowDirection        getShowType()   const { return m_showType;}
    inline qreal            getOpacity()    const { return m_nOpacity; }
    inline unsigned int     getTimeout()    const { return m_nTimeout; }
    inline QFont            getFont()       const { return m_font; }
    inline QColor           getBgColor()    const { return m_bgColor; }
    inline QColor           getFontColor()  const { return m_textColor; }
    inline std::string      getFileName()   const { return m_sFileName; }

    void load();
    void save();
};



#endif // CONFIG_H
