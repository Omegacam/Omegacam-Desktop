#include "home.h"
#include "./ui_home.h"

#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QScrollArea>

home::home(QWidget *parent):QMainWindow(parent), ui(new Ui::home){
    ui->setupUi(this);
    rightScrollAreaWidth = getRootWindowSize().height() * rightScrollAreaWidthRatio;
    //QScrollArea* rightScrollArea = new QScrollArea(this);

    //QPushButton* testButton = new QPushButton(this);
    //testButton->setText("Test Button");
    //testButton->setGeometry(0, 0, 100, 100);
    //connect(testButton, &QPushButton::clicked, this, &home::buttonClicked);
    //testButton->show();
    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    rightScrollArea->setAutoFillBackground(true);
  //  int rightScrollAreaWidth = 100;
    rightScrollArea->setGeometry(getRootWindowSize().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, getRootWindowSize().height());
    rightScrollArea->setPalette(p);
    rightScrollArea->show();
}

QSize home::getRootWindowSize(){
    return this->size();
}

void home::buttonClicked(){
    //qInfo() << "clicked" << endl;
}

void home::resizeEvent(QResizeEvent*){
    qInfo() << "resize: " << getRootWindowSize();
    rightScrollAreaWidth = getRootWindowSize().height() * rightScrollAreaWidthRatio;
    rightScrollArea->setGeometry(getRootWindowSize().width() - rightScrollAreaWidth, 0, rightScrollAreaWidth, getRootWindowSize().height());
}

home::~home(){
    delete ui;
}

