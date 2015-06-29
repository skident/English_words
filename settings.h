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


public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_buttonBox_accepted();
    void on_chooseFormColor_clicked();
    void on_chooseTextColor_clicked();

    void on_chooseFont_clicked();
    void on_chooseFileName_clicked();
    void on_buttonBox_rejected();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
