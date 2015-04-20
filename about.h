#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>


namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

    void closeEvent(QCloseEvent * e);

private slots:
    void on_close_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
