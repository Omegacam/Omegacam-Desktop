#ifndef _CAMERALISTWIDGET_H_
#define _CAMERALISTWIDGET_H_

#include <QWidget>
#include "../common_includes.h"

#include "../Backend/backendStructs.h"

class home;
class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr, home *rootparent = nullptr);
    ~CameraListWidget();

    void updateList(vector<discoveryDataPacket> data);

private:
    QPushButton* CreateChildButton(int num, home *rootparent);
    QWidget* parentptr = nullptr;

    void resizeEvent(QResizeEvent*);
signals:

};

#endif // _CAMERALISTWIDGET_H_
