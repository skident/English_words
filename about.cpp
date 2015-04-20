#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_close_clicked()
{
    delete this;
}

void About::closeEvent(QCloseEvent * e)
{
     if ( e )
        emit(on_close_clicked());
}
