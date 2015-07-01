#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QObject>
#include <QTabWidget>

class SettingsView : public QObject
{
    Q_OBJECT

private:
    QWidget*    m_wgt_MainWindow;


    QWidget* GetAppearanceTab();
    QWidget* GetLogicTab();
    QLayout* GetButtons();

public:
    SettingsView();
    virtual ~SettingsView();
};

#endif // SETTINGSVIEW_H
