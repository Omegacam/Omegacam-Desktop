#include "UI/home.h"

#include "common_includes.h"
#include "src/Backend/Network/communication.h"
#include "src/Backend/backendDelegate.h"

#include <thread>
#include <chrono>
#include <future>


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

    auto concurrent = std::async(std::launch::async, [&] {
        backendDelegate::start();
        });
    return a.exec();
}
