#include "config.h"


#include <QFile>
#include <QXmlStreamReader>
#include <QIODevice>
#include <QDebug>
#include <sstream>

using namespace std;

Config* Config::m_self = NULL;

Config::Config()
{
    setDirection(showForward);
    setOpacity(1);
    setTimeout(10);
    setFont(QFont());
    setBgColor(QColor(200, 200, 0));
    setFontColor(QColor(0,0,0));
    setFileName("D:\\words.txt");

//    if ( QFile::exists("config.xml") == false )
//    {
//        setShowType(engRus);
//        setOpacity(100);
//        setTimeout(10);
//        setFont(QFont());
//        setBgColor(QColor(200, 200, 0));
//        setFontColor(QColor(0,0,0));
//    }
//    else
//    {
//        load settings from file
//    }
}

void Config::load()
{
    QFile* xmlFile = new QFile("config.xml");
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Load XML File Problem" << endl << "Couldn't open xmlfile.xml to load settings for download";
        //TODO: offer to generate default config.xml
        return;
    }

    QXmlStreamReader* xmlReader = new QXmlStreamReader(xmlFile);


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

            qDebug() << xmlReader->name() << " : " << xmlReader->readElementText();
            setParam(xmlReader->name(), xmlReader->readElementText());
        }
    }

    if(xmlReader->hasError())
    {
        qDebug() << "xmlFile.xml Parse Error" << endl << xmlReader->errorString();
        //TODO: offer to generate default config.xml
        return;
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();
}

void Config::setParam(const QStringRef sName, const QString sValue)
{
    if (sName == "bgcolor")
    {
        QColor color(QRgb(sValue.toInt()));
        setBgColor(color);
    }
    else if (sName == "fontcolor")
    {
        QColor color(QRgb(sValue.toInt()));
        setFontColor(color);
    }
    else if (sName == "fontsize")
    {
        QFont font;
        font.setPixelSize(sValue.toInt());
        setFont(font);
    }
    else if (sName == "timeout")
    {
        setTimeout(sValue.toInt());
    }
    else if (sName == "opacity")
    {
        qreal opacity = qreal(sValue.toFloat()) / 100;
        setOpacity(opacity);
    }
    else if (sName == "filename")
    {
        setFileName(sValue.toStdString());
    }
    else if (sName == "direction")
    {
        eShowDirection direct = showForward;
        if (sValue != "0")
            direct = showBackward;

        setDirection(direct);
    }
}

