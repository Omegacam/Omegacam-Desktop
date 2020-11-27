#include "home.h"

#include "common_includes.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    home w;
    w.setWindowTitle("Omegacam");
    QPalette homeP;
    homeP.setColor(QPalette::Window, primaryBackgroundColor);
    w.setAutoFillBackground(true);
    w.setPalette(homeP);
    w.show();
    //w.rightScrollArea->widget();
    return a.exec();
}
