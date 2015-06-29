#include "config.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QIODevice>
#include <QDebug>
#include <iostream>

using namespace std;

Config* Config::m_self = NULL;

Config::Config()
    : m_sConfigFileName("config___________.xml")
    , m_pXmlFile(nullptr)
{
    m_pXmlFile = new QFile(m_sConfigFileName);

    //init tags names
    m_tagName[tag_form_bgcolor]     = "form_bgcolor";
    m_tagName[tag_form_opacity]     = "form_opacity";
    m_tagName[tag_font_family]      = "font_family";
    m_tagName[tag_font_color]       = "font_color";
    m_tagName[tag_font_size]        = "font_size";
    m_tagName[tag_font_bold]        = "font_bold";
    m_tagName[tag_font_italic]      = "font_italic";
    m_tagName[tag_words_filename]   = "words_filename";
    m_tagName[tag_words_timeout]    = "words_timeout";
    m_tagName[tag_words_direction]  = "words_direction";

    //init tags values
    m_tagValue[tag_form_bgcolor]    = "#111111";
    m_tagValue[tag_form_opacity]    = "50";
    m_tagValue[tag_font_family]     = QFont().toString();
    m_tagValue[tag_font_color]      = "#121212";
    m_tagValue[tag_font_color]      = "#233221";
    m_tagValue[tag_font_size]       = "12";
    m_tagValue[tag_font_bold]       = "1";
    m_tagValue[tag_font_italic]     = "0";
    m_tagValue[tag_words_filename]  = "D:\\words.txt";
    m_tagValue[tag_words_timeout]   = "8";
    m_tagValue[tag_words_direction] = "0";
}

Config::~Config()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete m_self;
    delete m_pXmlFile;
}

bool Config::load()
{
    if (!m_pXmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Load XML File Problem" << endl << "Couldn't open xmlfile.xml to load settings for download";
        //TODO: offer to generate default config.xml
        return false;
    }

    QString sFirstPart = "";
    QXmlStreamReader* xmlReader = new QXmlStreamReader(m_pXmlFile);

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();

        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument)
            continue;

        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement)
        {
            //skip root element
            if(xmlReader->name() == "config")
                continue;

//            if(xmlReader->name() == "font" || xmlReader->name() == "form" || xmlReader->name() == "words")
//            {
////                sFirstPart = xmlReader->name().toString() + "_";
//                continue;
//            }

            QString sTag = sFirstPart + xmlReader->name().toString();
            QString sValue = xmlReader->readElementText();
            cout << sTag.toStdString() << " : " << sValue.toStdString() << endl;

            //set read params
            for (auto it : m_tagName)
            {
                if (it.second == sTag)
                {
                    m_tagValue[it.first] = sValue;
                    break;
                }
            }
        }
    }

    if(xmlReader->hasError())
    {
        qDebug() << "xmlFile.xml Parse Error" << endl << xmlReader->errorString();
        //TODO: offer to generate default config.xml

        m_pXmlFile->close();
        return save();
    }

    //close reader and flush file
    xmlReader->clear();
    m_pXmlFile->close();

    return true;
}

bool Config::save()
{
    m_pXmlFile->close();
    m_pXmlFile->open(QIODevice::WriteOnly | QIODevice::Text);

    QXmlStreamWriter xmlWriter(m_pXmlFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("config");
        for (auto it : m_tagName)
            xmlWriter.writeTextElement(it.second, m_tagValue[it.first]);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    m_pXmlFile->close();

    return true;
}

void Config::setParam(const eTag tagId, const QString sValue)
{
    if (m_tagName.find(tagId) != m_tagName.end())
        m_tagValue[tagId] = sValue;
}

QString Config::getParam(const eTag tagId)
{
    if (m_tagName.find(tagId) != m_tagName.end())
        return m_tagValue[tagId];
    return "";
}

void Config::showConfig()
{
    for (auto it : m_tagName)
        cout << it.second.toStdString() << " | " << (m_tagValue[it.first]).toStdString() << endl;
}
