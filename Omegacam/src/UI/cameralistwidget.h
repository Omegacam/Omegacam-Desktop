#ifndef CAMERALISTWIDGET_H
#define CAMERALISTWIDGET_H

#include <QWidget>
#include "../common_includes.h"
#include "home.h"

class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr, home *rootparent = nullptr);
    ~CameraListWidget();

private:
    QPushButton* CreateChildButton(int num, home *rootparent);
    QWidget* parentptr = nullptr;

    void resizeEvent(QResizeEvent*);
signals:

};

#endif // CAMERALISTWIDGET_H
