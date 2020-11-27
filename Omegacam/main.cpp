#include "home.h"

#include "common_includes.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    home w;
    w.setWindowTitle("Omegacam");
    QPalette homeP;
    homeP.setColor(QPalette::Background, primaryBackgroundColor);
    w.setAutoFillBackground(true);
    w.setPalette(homeP);
    w.show();
    return a.exec();
}
