#ifndef CAMERALISTWIDGET_H
#define CAMERALISTWIDGET_H

#include <QWidget>
#include "common_includes.h"

class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr);
    ~CameraListWidget();

private:
    QPushButton* CreateChildButton(int num);
    QWidget* parentptr = nullptr;

    void resizeEvent(QResizeEvent*);
signals:

};

#endif // CAMERALISTWIDGET_H
