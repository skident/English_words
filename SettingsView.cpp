#include "SettingsView.h"

#include <QDebug>

#include <QTabWidget>
#include <QLabel>
#include <QToolButton>
#include <QSpinBox>
#include <QSpacerItem>
#include <QLayout>
#include <QPushButton>
#include <QVector>
#include <QComboBox>

SettingsView::SettingsView()
    : m_wgt_MainWindow(nullptr)
{
    qDebug() << __FUNCTION__;

    QTabWidget* wgt_tabWidget = new QTabWidget();
    QWidget* wgt_ViewSettings = GetAppearanceTab();
    QWidget* wgt_LogicSettings = GetLogicTab();

    wgt_tabWidget->addTab(wgt_ViewSettings,     "&Appearance");
    wgt_tabWidget->addTab(wgt_LogicSettings,    "&Logic");

    QLayout* layButtons = GetButtons();

    QVBoxLayout*    lay_MainLayout  = new QVBoxLayout();
    lay_MainLayout->addWidget(wgt_tabWidget);
    lay_MainLayout->addLayout(layButtons);


    m_wgt_MainWindow = new QWidget();
    m_wgt_MainWindow->setLayout(lay_MainLayout);
    m_wgt_MainWindow->show();
//    wgt_tabWidget->show();
}

SettingsView::~SettingsView()
{
    qDebug() << __FUNCTION__;

    delete m_wgt_MainWindow;
}

QLayout* SettingsView::GetButtons()
{
    //buttons
    QHBoxLayout*    lay_Buttons     = new QHBoxLayout();
    QPushButton*    but_Ok      = new QPushButton("OK");
    QPushButton*    but_Apply   = new QPushButton("Apply");
    QPushButton*    but_Cancel  = new QPushButton("Cancel");

    lay_Buttons->addWidget(but_Ok);
    lay_Buttons->addWidget(but_Apply);
    lay_Buttons->addWidget(but_Cancel);

    return lay_Buttons;
}

QWidget* SettingsView::GetLogicTab()
{
    QWidget*        wgt_MainWidget  = new QWidget();
    QVBoxLayout*    lay_MainLayout  = new QVBoxLayout();
    QHBoxLayout*    lay_Horizontal  = nullptr;

    //first column
    QLabel*         lbl_LangOrder       = new QLabel("Language Order");
    QLabel*         lbl_TimerTimeout    = new QLabel("Timer Timeout");
    QLabel*         lbl_DictFileName    = new QLabel("Dictinary File");

    //second column
    QSpacerItem*    spc_Hor1    = new QSpacerItem(100, 10);
    QSpacerItem*    spc_Hor2    = new QSpacerItem(100, 10);
    QSpacerItem*    spc_Hor3    = new QSpacerItem(100, 10);

    //3 column
    QComboBox*      cmb_LangOrder   = new QComboBox();
    cmb_LangOrder->addItem("First -> Second");
    cmb_LangOrder->addItem("Second -> First");

    QSpinBox*       spn_Timeout  = new QSpinBox();
    spn_Timeout->setMinimum(5);
    spn_Timeout->setMaximum(10);

    QToolButton*    tlb_FileName    = new QToolButton();

    QSpacerItem*    spc_Ver1    = new QSpacerItem(10, 100);
    QSpacerItem*    spc_Ver2    = new QSpacerItem(10, 100);

//    lay_MainLayout->addItem(spc_Ver1);


    //first line
    lay_Horizontal = new QHBoxLayout();
    lay_Horizontal->addWidget(lbl_LangOrder);
    lay_Horizontal->addItem(spc_Hor1);
    lay_Horizontal->addWidget(cmb_LangOrder);
    lay_MainLayout->addLayout(lay_Horizontal);

    //second line
    lay_Horizontal = new QHBoxLayout();
    lay_Horizontal->addWidget(lbl_TimerTimeout);
    lay_Horizontal->addItem(spc_Hor2);
    lay_Horizontal->addWidget(spn_Timeout);
    lay_MainLayout->addLayout(lay_Horizontal);

    //third line
    lay_Horizontal = new QHBoxLayout();
    lay_Horizontal->addWidget(lbl_DictFileName);
    lay_Horizontal->addItem(spc_Hor3);
    lay_Horizontal->addWidget(tlb_FileName);
    lay_MainLayout->addLayout(lay_Horizontal);

//    lay_MainLayout->addItem(spc_Ver2);

    wgt_MainWidget->setLayout(lay_MainLayout);

    return wgt_MainWidget;
}

QWidget* SettingsView::GetAppearanceTab()
{
    QVector<QVBoxLayout*> vec_verLayouts;
    QVector<QHBoxLayout*> vec_horLayouts;


    QLayout* currLayout = nullptr;

    for (int i = 0; i < 20; i++)
    {
        QVBoxLayout* tmpVertical = new QVBoxLayout();
        vec_verLayouts.push_back(tmpVertical);

        QHBoxLayout* tmpHorizontal = new QHBoxLayout();
        vec_horLayouts.push_back(tmpHorizontal);
    }

    QWidget*        wgt_MainWidget    = new QWidget();
    QVBoxLayout*    lay_MainLayout      = new QVBoxLayout();

    QLabel*         lbl_WinOpacity  = new QLabel("Window Opacity");
    QLabel*         lbl_WinColor    = new QLabel("Window Color");
    QLabel*         lbl_FontColor   = new QLabel("Font Color");
    QLabel*         lbl_FontType    = new QLabel("Font Type");

    QSpacerItem*    spc_Hor1    = new QSpacerItem(100, 10);
    QSpacerItem*    spc_Hor2    = new QSpacerItem(100, 10);
    QSpacerItem*    spc_Hor3    = new QSpacerItem(100, 10);
    QSpacerItem*    spc_Hor4    = new QSpacerItem(100, 10);

    QSpinBox*       spn_WinOpacity  = new QSpinBox();
    spn_WinOpacity->setMinimum(30);
    spn_WinOpacity->setMaximum(100);

    QToolButton*    tlb_WinColor    = new QToolButton();
    QToolButton*    tlb_FontColor   = new QToolButton();
    QToolButton*    tlb_FontType    = new QToolButton();


    //first line
    currLayout = vec_horLayouts.front();
    currLayout->addWidget(lbl_WinOpacity);
    currLayout->addItem(spc_Hor1);
    currLayout->addWidget(spn_WinOpacity);
    vec_horLayouts.removeFirst();
    lay_MainLayout->addLayout(currLayout);

    //second line
    currLayout = vec_horLayouts.front();
    currLayout->addWidget(lbl_WinColor);
    currLayout->addItem(spc_Hor2);
    currLayout->addWidget(tlb_WinColor);
    vec_horLayouts.removeFirst();
    lay_MainLayout->addLayout(currLayout);

    //third line
    currLayout = vec_horLayouts.front();
    currLayout->addWidget(lbl_FontColor);
    currLayout->addItem(spc_Hor3);
    currLayout->addWidget(tlb_FontColor);
    vec_horLayouts.removeFirst();
    lay_MainLayout->addLayout(currLayout);

    //fourth line
    currLayout = vec_horLayouts.front();
    currLayout->addWidget(lbl_FontType);
    currLayout->addItem(spc_Hor4);
    currLayout->addWidget(tlb_FontType);
    vec_horLayouts.removeFirst();
    lay_MainLayout->addLayout(currLayout);


    wgt_MainWidget->setLayout(lay_MainLayout);


    return wgt_MainWidget;
}

