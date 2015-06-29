#pragma once

#include <QLabel>

class PushLabel : public QLabel
{
    Q_OBJECT
public:
    PushLabel();
    ~PushLabel();

signals:
    void clicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

};
