#include "home.h"
#include "./ui_home.h"

#include "common_includes.h"

#include "cameralistwidget.h"

home::home(QWidget *parent):QMainWindow(parent), ui(new Ui::home){
    ui->setupUi(this);
    rightScrollAreaWidth = getRootWindowSize().height() * rightScrollAreaWidthRatio;

    QPalette p;
    p.setColor(QPalette::Background, Qt::blue);
    rightScrollArea->setAutoFillBackground(true);
    rightScrollArea->setGeometry(getRootWindowSize().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, getRootWindowSize().height());
    rightScrollArea->setPalette(p);

    CameraListWidget *cameraList = new CameraListWidget(rightScrollArea);

    //cameraList->size
    rightScrollArea->setWidget(cameraList);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    rightScrollArea->show();
}

QSize home::getRootWindowSize(){
    return this->size();
}

void home::buttonClicked(){
    //qInfo() << "clicked" << endl;
}

void home::resizeEvent(QResizeEvent*){
    //qInfo() << "resize: " << getRootWindowSize();
    rightScrollAreaWidth = getRootWindowSize().height() * rightScrollAreaWidthRatio;
    rightScrollArea->setGeometry(getRootWindowSize().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, getRootWindowSize().height());
    //rightScrollArea->widget()->resize(rightScrollArea->size().width(), rightScrollArea->size().height());
}

home::~home(){
    delete ui;
}

