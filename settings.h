#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QColor>
#include <QFont>
#include "config.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

    explicit Settings(QWidget *parent = 0);
    ~Settings();

public:
    static Settings* get();

    //getters
//    bool inline             isNewSettings() const { return bNewSettings;    }
//    bool inline             isEngRus()      const { return bEngRus;         }
//    unsigned char inline    getOpacity()    const { return nOpacity;        }
//    unsigned char inline    getTimeout()    const { return nTimeout;        }
//    void inline             setSettingsState(bool bState) { bNewSettings = bState; }

private slots:
    void on_buttonBox_accepted();
    void on_chooseFormColor_clicked();
    void on_chooseTextColor_clicked();

    void on_chooseFont_clicked();

private:
    Ui::Settings *ui;
    static Settings* _self;
    Config* pCfg;

//    bool            bNewSettings;
//    bool            bEngRus;
//    unsigned char   nOpacity;
//    unsigned char   nTimeout;
//    QFont           font;

//    QColor         m_bgColor;
//    QColor         m_textColor;
};

#endif // SETTINGS_H
