#ifndef _CAMERALISTWIDGET_H_
#define _CAMERALISTWIDGET_H_

#include <QWidget>
#include "../common_includes.h"

#include "../Backend/backendStructs.h"

#include "Custom/CameraPushButton.h"

class home;
class CameraListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraListWidget(QWidget *parent = nullptr, home *rootparent = nullptr);
    ~CameraListWidget();

    void updateList(vector<discoveryDataPacket> data);

public slots:
    void CreateChildButton(discoveryDataPacket data);

private slots:
    void updateCameraStream();

private:
    QWidget* parentptr = nullptr;
    home* homeptr = nullptr;

    int listSize = 0; // stores the number of child buttons

    void resizeEvent(QResizeEvent*);

    void clearList();
    void updateButton(CameraPushButton* button, discoveryDataPacket data);

};

#endif // _CAMERALISTWIDGET_H_
