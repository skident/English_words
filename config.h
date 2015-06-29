#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QFont>
#include <QFile>
#include <string>
#include <QString>

#include <map>

class Config
{
public:
    enum eShowDirection
    {
        showForward,
        showBackward
    };

    enum eTag
    {
        tag_form_bgcolor,
        tag_form_opacity,

        tag_font_color,
        tag_font_family,
        tag_font_bold,
        tag_font_italic,
        tag_font_size,

        tag_words_timeout,
        tag_words_filename,
        tag_words_direction
    };


private:
    static Config*  m_self;

    QString         m_sConfigFileName;
    QFile*          m_pXmlFile;

    std::map<eTag, QString> m_tagName;
    std::map<eTag, QString> m_tagValue;

    Config();
    ~Config();

public:
    static Config* get()
    {
        if ( !m_self )
            m_self = new Config();
        return m_self;
    }

    void    setParam(const eTag tagId, const QString sValue);
    QString getParam(const eTag tagId);
    bool load();
    bool save();

    void showConfig();
};



#endif // CONFIG_H
