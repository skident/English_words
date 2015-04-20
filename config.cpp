#include "config.h"

Config* Config::m_self = NULL;

Config::Config()
{
    setShowType(showForward);
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
