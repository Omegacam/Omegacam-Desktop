#include "home.h"
#include "./ui_home.h"

#include "common_includes.h"

#include "cameralistwidget.h"

home::home(QWidget *parent):QMainWindow(parent), ui(new Ui::home){
    ui->setupUi(this);
    rightScrollAreaWidth = this->size().height() * rightScrollAreaWidthRatio;
    rightScrollArea = new QScrollArea(this);

    rightScrollArea->setFrameShape(QFrame::NoFrame);
    rightScrollArea->setGeometry(this->size().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, this->size().height());

    CameraListWidget *cameraList = new CameraListWidget(rightScrollArea, this);

    rightScrollArea->setWidget(cameraList);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //rightScrollArea->show();
}

void home::setMainContentStream(){
    qInfo() << "received event";
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton){ // sender is a button
        qInfo() << "sender is button";
    }
}

void home::resizeEvent(QResizeEvent*){
    //qInfo() << "resize: " << getRootWindowSize();
    rightScrollAreaWidth = this->size().height() * rightScrollAreaWidthRatio;
    rightScrollArea->setGeometry(this->size().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, this->size().height());
    rightScrollArea->widget()->resize(rightScrollArea->size().width(), rightScrollArea->size().height());
}

home::~home(){
    delete ui;
}

