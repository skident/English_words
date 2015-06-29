#include "PushLabel.h"
#include <QDebug>

PushLabel::PushLabel() :QLabel()
{
    qDebug() << __FUNCTION__;
}

PushLabel::~PushLabel()
{
    qDebug() << __FUNCTION__;
}


void PushLabel::mousePressEvent( QMouseEvent* event)
{
    qDebug() << __FUNCTION__;
    emit clicked();
}

