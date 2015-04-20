#pragma once

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QColor>
#include <QLabel>
#include <QFont>
#include "Words.h"

namespace Ui {
class Words;
}

class WordsController : public QMainWindow
{
    Q_OBJECT

    Ui::Words*              ui;
    static WordsController* m_self;
    QTimer*                 m_timer;
    QSystemTrayIcon*        m_trIcon;
    QLabel*                 m_lbl_words;
    QPoint                  m_mpos;
    Words*                  m_ptrWords;

    explicit WordsController(QWidget *parent = 0);
    ~WordsController();

    void delay(int millisecondsToWait);

public:
    void Load();
    static WordsController* Get();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * e);


private slots:
    void showHide(QSystemTrayIcon::ActivationReason); //WTF ?!
    void ShowNextWord();


    //context menu
    void exit_action();
    void about_action();
    void settings_action();

public slots:
    void showContextMenu(const QPoint& pos);
//    void settingsUpdate(bool bEngRus,  unsigned char nOpacity, unsigned char nTimeout);
//    void applySettings(bool bEngRus, unsigned char nOpacity, unsigned char nTimeout, QFont font, QColor formColor, QColor textColor);
//    void onFormDbClick();

    void applySettings();


};
