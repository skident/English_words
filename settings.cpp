#include "settings.h"
#include "ui_settings.h"
#include "WordsController.h"

#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>

#include <QDebug>

Settings* Settings::_self = NULL;

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
//    , bNewSettings(true)
//    , bEngRus(true)
//    , nOpacity(0)
//    , nTimeout(10)
//    , m_bgColor(198, 191, 255)
//    , m_textColor(0, 0, 0)
{
    ui->setupUi(this);
    pCfg = Config::get();

    QColor bgColor = pCfg->getBgColor();
    QColor fontColor = pCfg->getFontColor();
    QString style = "background-color: rgb(%1, %2, %3);";
    ui->chooseFormColor->setStyleSheet(style.arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()));
    ui->chooseTextColor->setStyleSheet(style.arg(fontColor.red()).arg(fontColor.green()).arg(fontColor.blue()));

//    qDebug() << font;
}

Settings::~Settings()
{
    delete ui;
    delete _self;
//    delete pCfg;
}


Settings* Settings::get()
{
    if ( !_self )
        _self = new Settings();
    return _self;
}

void Settings::on_buttonBox_accepted()
{
    pCfg->setShowType( (ui->combo_show_type->currentIndex() == 0 ? Config::showForward : Config::showBackward));
    pCfg->setOpacity(qreal(ui->opacity->value()) / 100);
    pCfg->setTimeout(ui->nTimeOut->value());
    /*pCfg->setBgColor(m_bgColor);
    pCfg->setFontColor(m_textColor);
    pCfg->setFont(font)*/;


//    setSettingsState(true);

//    emit(Words::get()->applySettings(bEngRus,nOpacity, nTimeout, font, m_bgColor, m_textColor));
    emit(WordsController::Get()->applySettings());
    this->hide();
}

void Settings::on_chooseFormColor_clicked()
{
    QColor m_bgColor = QColorDialog::getColor();

    if (!m_bgColor.isValid() )
        return;

    QString style = "background-color: rgb(%1, %2, %3);";
    ui->chooseFormColor->setStyleSheet(style.arg(m_bgColor.red()).arg(m_bgColor.green()).arg(m_bgColor.blue()));

    pCfg->setBgColor(m_bgColor);
}

void Settings::on_chooseTextColor_clicked()
{
    QColor m_textColor = QColorDialog::getColor();

    if (!m_textColor.isValid() )
        return;


    QString style = "background-color: rgb(%1, %2, %3);";
    ui->chooseTextColor->setStyleSheet(style.arg(m_textColor.red()).arg(m_textColor.green()).arg(m_textColor.blue()));

    pCfg->setFontColor(m_textColor);
}

void Settings::on_chooseFont_clicked()
{
    bool ok;
    QFont tmpFont = QFontDialog::getFont(&ok, pCfg->getFont());
    if ( ok )
        pCfg->setFont(tmpFont);
}
