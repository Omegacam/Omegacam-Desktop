#include "cameralistwidget.h"
#include "home.h"

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
    
    for (int i = 0; i < 20; i++){
       CreateChildButton(i);
    }


    this->show();
}

CameraListWidget::~CameraListWidget() {}

//

void CameraListWidget::updateList(vector<discoveryDataPacket> data) {
    logs::stat("update list called");
    
    clearList();

    for (int i = 0; i < 10; i++) {
//        this->layout()->addWidget(CreateChildButton(i));
        QMetaObject::invokeMethod(this, "CreateChildButton", Q_ARG(int, i));
    }
}

void CameraListWidget::clearList() {
    clearLayout(this->layout());
}

void CameraListWidget::clearLayout(QLayout* layout) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        QWidget* widget;
        if (widget = item->widget()) {
            widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void CameraListWidget::CreateChildButton(int num){
    QPushButton *c = new QPushButton();
    
    QLabel *title = new QLabel(QString::fromStdString("button #" + std::to_string(num) + " LONG LONG LONG LONG LONG LONG LONG LONG LONG TEXT"));
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

    logs::stat("create child button " + to_string(num));

    //connect(c, &QPushButton::clicked, rootparent, &home::setMainContentStream);
    this->layout()->addWidget(c);
}

void CameraListWidget::resizeEvent(QResizeEvent*){
    for (int i = 0; i < this->layout()->count(); i++){
        QWidget *button = this->layout()->itemAt(i)->widget();
        if (button){
            button->setMaximumWidth(this->size().width());
        }
        else{
            logs::crit("Non button found");
        }
    }
}

