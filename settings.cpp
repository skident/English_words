#include "settings.h"
#include "ui_settings.h"
#include "WordsController.h"

#include <QColor>
#include <QFont>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

#include <QDebug>

//Settings* Settings::_self = NULL;

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    if (Config::get()->load())
    {
        //init elements on form
        //TODO: add opacity slider init

        QColor bgColor(Config::get()->getParam(Config::tag_form_bgcolor));
        QColor fontColor(Config::get()->getParam(Config::tag_font_color));

        QString style = "background-color: rgb(%1, %2, %3);";
        ui->chooseFormColor->setStyleSheet(style.arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()));
        ui->chooseTextColor->setStyleSheet(style.arg(fontColor.red()).arg(fontColor.green()).arg(fontColor.blue()));
    }
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_chooseFormColor_clicked()
{
    QColor bgColor = QColorDialog::getColor();
    if (!bgColor.isValid() )
        return;

    Config::get()->setParam(Config::tag_form_bgcolor, bgColor.name());

    QString style = "background-color: rgb(%1, %2, %3);";
    ui->chooseFormColor->setStyleSheet(style.arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()));
}

void Settings::on_chooseTextColor_clicked()
{
    QColor fontColor = QColorDialog::getColor();
    if (!fontColor.isValid())
        return;

    Config::get()->setParam(Config::tag_font_color, fontColor.name());

    QString style = "background-color: rgb(%1, %2, %3);";
    ui->chooseTextColor->setStyleSheet(style.arg(fontColor.red()).arg(fontColor.green()).arg(fontColor.blue()));

}

void Settings::on_chooseFont_clicked()
{
    bool ok = false;
    QFont tmpFont = QFontDialog::getFont(&ok/*, Config::get()->getParam(Config::tag_font)*/);
    if ( ok )
    {
        qDebug() << __FUNCTION__ << " " << tmpFont.toString();
        Config::get()->setParam(Config::tag_font_family, tmpFont.toString());
        Config::get()->setParam(Config::tag_font_size,   QString::number(tmpFont.pointSize()));
        Config::get()->setParam(Config::tag_font_bold,   QString::number(tmpFont.bold()));
        Config::get()->setParam(Config::tag_font_italic, QString::number(tmpFont.italic()));
    }
}

void Settings::on_chooseFileName_clicked()
{
    QString sConfigFileName = Config::get()->getParam(Config::tag_words_filename);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), sConfigFileName, tr("Text files (*.txt)"));
    if (fileName != "")
        Config::get()->setParam(Config::tag_words_filename, fileName);
}


//Accepted or Rejected was clicked
void Settings::on_buttonBox_accepted()
{
    Config::get()->setParam(Config::tag_words_direction,   QString::number(ui->combo_show_type->currentIndex()));
    Config::get()->setParam(Config::tag_form_opacity,      QString::number(ui->opacity->value()));
    Config::get()->setParam(Config::tag_words_timeout,     QString::number(ui->nTimeOut->value()));
    Config::get()->save();
}

void Settings::on_buttonBox_rejected()
{
    Config::get()->load(); //restore settings
}
