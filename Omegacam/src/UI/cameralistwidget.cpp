#include "cameralistwidget.h"
#include "home.h"

#include "../common_includes.h"

CameraListWidget::CameraListWidget(QWidget *parent, home *rootparent) : QWidget(parent){

    this->parentptr = parent;

    this->setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Window, secondaryBackgroundColor);
    //p.setColor(QPalette::)
    this->setPalette(p);

    QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->setGeometry()
    //layout->setGeometry(QRect(0, 0, 1, 1));
    layout->setContentsMargins(10, 10, 10, 10);

    for (int i = 0; i < 20; i++){
       layout->addWidget(CreateChildButton(i, rootparent));
    }

    this->setLayout(layout);

    //this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    //this->setFixedWidth(parentptr->size().width()

    this->show();
    //qInfo() << "Constructor called";
}

QPushButton* CameraListWidget::CreateChildButton(int num, home *rootparent){
    QPushButton *c = new QPushButton(this);
    //c->setText(QString::fromStdString("button #" + std::to_string(num) + "LONG \n LONG LONG LONG LONG LONG LONG LONG LONG TEXT"));

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
    //c->resize(0, 80);

    c->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    connect(c, &QPushButton::clicked, rootparent, &home::setMainContentStream);
    return c;
}

void CameraListWidget::resizeEvent(QResizeEvent*){
    //qInfo() << "resize called from widget";
    for (int i = 0; i < this->layout()->count(); i++){
        QWidget *button = this->layout()->itemAt(i)->widget();
        if (button){
            button->setMaximumWidth(this->size().width());
        }
        else{
            qCritical() << "Invalid widget found in right bar";
        }
    }
    //this->setFixedWidth(parentptr->size().width());
}

CameraListWidget::~CameraListWidget(){

}
