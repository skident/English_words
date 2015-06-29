#pragma once

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QColor>
#include <QLabel>
#include <QFont>
#include "Words.h"

#include <QToolButton>
#include <QHBoxLayout>
#include <QWidget>

namespace Ui {
class Words;
}

class WordsController : public QMainWindow
{
    Q_OBJECT

    Ui::Words*              ui;
    QWidget*                m_pMainWidget;
    QLabel*                 m_pLabelWords;
    Words*                  m_pWords;
    QToolButton*            m_pButPlay;
    QToolButton*            m_pButPause;
    QHBoxLayout*            m_pMainLayout;
    QTimer*                 m_pTimer;
    QPoint                  m_mpos;
    int                     m_nTimeout;

//    void delay(int millisecondsToWait);

public:
    explicit WordsController(QWidget *parent = 0);
    ~WordsController();

    void Start();
    void Stop();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * e);

    bool eventFilter(QObject* obj, QEvent* e);

    void closeEvent(QCloseEvent * e);


private slots:
    void ShowNextWord();
    void Play();
    void Pause();


    //context menu
    void exit_action();
    void about_action();
    void settings_action();

    void on_close_clicked();

public slots:
    void showContextMenu(const QPoint& pos);
    void applySettings();

};
