#include "AboutView.h"

#include <QBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPixmap>
#include <QApplication>
#include <QPushButton>

#include <QDebug>


AboutView::AboutView()
    : m_wgt_MainWindow(nullptr)
{
    m_wgt_MainWindow            = new QWidget();
    QHBoxLayout* lay_MainLayout = new QHBoxLayout();
    QHBoxLayout* lay_ButLayout  = new QHBoxLayout();
    QVBoxLayout* lay_VerLayout  = new QVBoxLayout();
    QLabel*      lbl_Logo       = new QLabel();
    QLabel*      lbl_Title      = new QLabel("English Words ver. 1.0");
    QLabel*      lbl_Info       = new QLabel("Not very long info about this software and author");
    QLabel*      lbl_Copyright  = new QLabel("Copyright trololo");
    QPushButton* but_Close      = new QPushButton("Close");
    QSpacerItem* spacer1        = new QSpacerItem(100, 1);

    lay_ButLayout->addItem(spacer1);
    lay_ButLayout->addWidget(but_Close);

    lay_VerLayout->addWidget(lbl_Title);
    lay_VerLayout->addWidget(lbl_Info);
    lay_VerLayout->addWidget(lbl_Copyright);
    lay_VerLayout->addLayout(lay_ButLayout);

    lbl_Logo->setPixmap(QPixmap(QApplication::applicationDirPath() + "/icons/logo.jpg"));
    lay_MainLayout->addWidget(lbl_Logo);
    lay_MainLayout->addLayout(lay_VerLayout);

    m_wgt_MainWindow->setLayout(lay_MainLayout);
    m_wgt_MainWindow->show();
}

AboutView::~AboutView()
{
    qDebug() << __FUNCTION__;

    delete m_wgt_MainWindow; //must deletes after all elements on it
}

