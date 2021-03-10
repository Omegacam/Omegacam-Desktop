#include "cameralistwidget.h"
#include "home.h"

#include "../common_includes.h"

CameraListWidget::CameraListWidget(QWidget *parent, home *rootparent) : QWidget(parent){

    this->parentptr = parent;

    this->setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Window, secondaryBackgroundColor);
    this->setPalette(p);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);

    for (int i = 0; i < 20; i++){
       layout->addWidget(CreateChildButton(i, rootparent));
    }

    this->setLayout(layout);

    this->show();
}

CameraListWidget::~CameraListWidget() {}

//

void CameraListWidget::updateList(vector<discoveryDataPacket> data) {
    logs::stat("update list called");
}

QPushButton* CameraListWidget::CreateChildButton(int num, home *rootparent){
    QPushButton *c = new QPushButton(this);

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

    //connect(c, &QPushButton::clicked, rootparent, &home::setMainContentStream);
    return c;
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

