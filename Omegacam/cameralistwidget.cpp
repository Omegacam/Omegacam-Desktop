#include "cameralistwidget.h"

#include "common_includes.h"

CameraListWidget::CameraListWidget(QWidget *parent) : QWidget(parent){

    this->parentptr = parent;

    this->setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Window, primaryBackgroundColor);
    this->setPalette(p);

    QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->setGeometry()
    //layout->setGeometry(QRect(0, 0, 1, 1));

    for (int i = 0; i < 200; i++){
       layout->addWidget(CreateChildButton(i));
    }

    this->setLayout(layout);

    this->show();
    //qInfo() << "Constructor called";
}

QPushButton* CameraListWidget::CreateChildButton(int num){
    QPushButton *c = new QPushButton(this);
    c->setText(QString::fromStdString("button #" + std::to_string(num)));
    c->setMinimumHeight(60);

    c->setAutoFillBackground(true);

    QPalette p = c->palette();
    p.setColor(QPalette::Button, secondaryBackgroundColor);
    c->setPalette(p);
    //c->update();

    //qInfo() << "has height4width - " << c->hasHeightForWidth() << endl;
    //connect(c, &QPushButton::clicked, this, &CameraListWidget::);
    return c;
}

void CameraListWidget::resizeEvent(QResizeEvent*){
    //qInfo() << "resize called from widget";
    //this->layout()->
}

CameraListWidget::~CameraListWidget(){

}
