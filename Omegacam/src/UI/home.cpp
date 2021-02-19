#include "home.h"
#include "./ui_home.h"

#include "cameralistwidget.h"

home* home::obj = nullptr;

home* home::getInstance() {
    if (home::obj == nullptr) {
        home::obj = new home();
    }
    return home::obj;
}

home::home(QWidget *parent):QMainWindow(parent), ui(new Ui::home){
    ui->setupUi(this);
    rightScrollAreaWidth = this->size().width() * rightScrollAreaWidthRatio;
    rightScrollArea = new QScrollArea(this);

    rightScrollArea->setFrameShape(QFrame::NoFrame);
    rightScrollArea->setGeometry(this->size().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, this->size().height());

    CameraListWidget *cameraList = new CameraListWidget(rightScrollArea, this);

    rightScrollArea->setWidget(cameraList);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightScrollArea->setStyleSheet(QString::fromUtf8(
    "QScrollBar:vertical {"
    "    border: 1px solid #999999;"
    "    background:white;"
    "    width:10px;    "
    "    margin: 0px 0px 0px 0px;"
    "}"
    "QScrollBar::handle:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0 rgb(66, 66, 66), stop: 0.5 rgb(66, 66, 66), stop:1 rgb(97, 97, 97));"
    "    min-height: 0px;"
    "}"
    "QScrollBar::add-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0 rgb(66, 66, 66), stop: 0.5 rgb(66, 66, 66),  stop:1 rgb(97, 97, 97));"
    "    height: 0px;"
    "    subcontrol-position: bottom;"
    "    subcontrol-origin: margin;"
    "}"
    "QScrollBar::sub-line:vertical {"
    "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
    "    stop: 0  rgb(66, 66, 66), stop: 0.5 rgb(66, 66, 66),  stop:1 rgb(97, 97, 97));"
    "    height: 0 px;"
    "    subcontrol-position: top;"
    "    subcontrol-origin: margin;"
    "}"
    ));
}

void home::setMainContentStream(){
    qInfo() << "received event";
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton){ // sender is a button
        qInfo() << "sender is button";
    }
}

void home::resizeEvent(QResizeEvent*){
    rightScrollAreaWidth = this->size().width() * rightScrollAreaWidthRatio;
    rightScrollArea->setGeometry(this->size().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, this->size().height());
    rightScrollArea->widget()->resize(rightScrollArea->size().width(), rightScrollArea->size().height());
}

home::~home(){
    delete ui;
}

