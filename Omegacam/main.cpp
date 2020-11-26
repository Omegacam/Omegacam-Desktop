#include "home.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    home w;
    w.setWindowTitle("Omegacam");
    w.show();
    return a.exec();
}
