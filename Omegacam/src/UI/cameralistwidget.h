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

signals:
public slots:
    void CreateChildButton(int num);

private:
    QWidget* parentptr = nullptr;
    home* homeptr = nullptr;

    void resizeEvent(QResizeEvent*);

    void clearList();

    void clearLayout(QLayout* layout);

};

#endif // _CAMERALISTWIDGET_H_
