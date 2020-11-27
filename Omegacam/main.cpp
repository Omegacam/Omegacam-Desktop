#include "home.h"
#

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    home w;
    w.setWindowTitle("Omegacam");
    QPalette homeP;
    homeP.setColor(QPalette::Background, Qt::white);
    w.setAutoFillBackground(true);
    w.setPalette(homeP);
    w.show();
    return a.exec();
}
