#include "cameralistwidget.h"
#include "home.h"
#include "miscellaneous.h"

#include "../common_includes.h"

CameraListWidget::CameraListWidget(QWidget *parent, home *rootparent) : QWidget(parent){

    this->parentptr = parent;
    this->homeptr = rootparent;

    this->setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Window, secondaryBackgroundColor);
    this->setPalette(p);

    QVBoxLayout *layout = new QVBoxLayout(this);
   
    layout->setContentsMargins(10, 10, 10, 10);

    this->setLayout(layout);
    
    /*for (int i = 0; i < 20; i++){
       CreateChildButton(i);
    }*/

    this->show();

    qRegisterMetaType<discoveryDataPacket>("discoveryDataPacket");
}

CameraListWidget::~CameraListWidget() {}

//

void CameraListWidget::updateList(vector<discoveryDataPacket> data) {
    logs::stat("update list called - " + to_string(data.size()));
    
    //clearList();

    /*for (discoveryDataPacket i : data) {
//        this->layout()->addWidget(CreateChildButton(i));
        QMetaObject::invokeMethod(this, "CreateChildButton", Q_ARG(discoveryDataPacket, i));
    }*/

    for (int i = 0; i < listSize; i++) {
        QLayoutItem* item = this->layout()->itemAt(i);
        if (item) {
           
            
            if (!item->widget()) { // checks if widget is valid
                logs::crit("Camera list item #" + to_string(i + 1) + " doesn't have a valid widget");
                continue;
            }

            if (i < data.size()) { // only need to update current button

                CameraPushButton* button = dynamic_cast<CameraPushButton*>(item->widget());
                if (button) {
                    logs::stat("updated button #" + to_string(i + 1));
                    updateButton(button, data[i]);
                }
                else {
                    logs::crit("Error in casting camera list button #" + to_string(i + 1));
                }
    
            }
            else { // remove current button as it's left over

                logs::stat("removing button #" + to_string(i + 1));
                item->widget()->deleteLater();

                if (QLayout* childLayout = item->layout()) { 

                    uimisc::clearLayout(childLayout);

                }

            }

        }
        else {
            logs::crit("No QLayoutItem found at position #" + to_string(i));
        }
    }

    // now, we must add any extra buttons left over
    if (listSize < data.size()) {
        for (int i = listSize; i < data.size(); i++) {
            logs::stat("creating new button #" + to_string(i + 1));
            QMetaObject::invokeMethod(this, "CreateChildButton", Q_ARG(discoveryDataPacket, data[i]));
        }
    }

    listSize = data.size();
}

void CameraListWidget::updateButton(CameraPushButton* button, discoveryDataPacket data) {
    QLayoutItem* item = button->layout()->itemAt(0);
    QWidget* widget = item->widget();
    if (widget) {
        QLabel* title = dynamic_cast<QLabel*>(widget);
        if (title) {
            title->setText(QString::fromStdString(data.deviceName));
            button->discoveryData = data;
        }
        else {
            logs::crit("update button has null title widget");
        }
    }
    else {
        logs::crit("update button has null widget pointer");
    }
}

void CameraListWidget::CreateChildButton(discoveryDataPacket data){
    CameraPushButton *c = new CameraPushButton();
    
    QLabel *title = new QLabel(QString::fromStdString(data.deviceName));
    title->setWordWrap(true);

    QHBoxLayout *titleLayout = new QHBoxLayout(c);
    titleLayout->addWidget(title, 0, Qt::AlignHCenter);

    c->setMinimumHeight(60);
    c->setMaximumWidth(this->parentptr->size().width());
    c->setAutoFillBackground(true);

    QPalette p = c->palette();
    p.setColor(QPalette::Button, secondaryBackgroundColor);
    c->setPalette(p);

    c->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    c->discoveryData = data;

    //logs::stat("create child button " + to_string(num));
    connect(c, &CameraPushButton::clicked, this, &CameraListWidget::updateCameraStream);
    
    this->layout()->addWidget(c);
}

//

void CameraListWidget::updateCameraStream() {
    CameraPushButton* senderButton = dynamic_cast<CameraPushButton*>(sender());
    if (senderButton) {
        logs::stat("got a camerapushbutton - " + senderButton->discoveryData.deviceName);
    }
}

void CameraListWidget::clearList() {
    uimisc::clearLayout(this->layout());
}

void CameraListWidget::resizeEvent(QResizeEvent*){
    for (int i = 0; i < this->layout()->count(); i++){
        QWidget *button = this->layout()->itemAt(i)->widget();
        if (button){
            button->setMaximumWidth(this->size().width());
        }
        else{
            logs::crit("Non button found in layout while resizing");
        }
    }
}

