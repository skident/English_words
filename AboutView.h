#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>


class AboutView: public QObject
{
    Q_OBJECT

private:
    QWidget*    m_wgt_MainWindow;

public:
    AboutView();
    virtual ~AboutView();
};

#endif // ABOUT_H
