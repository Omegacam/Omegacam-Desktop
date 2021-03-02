#include "UI/home.h"

#include "common_includes.h"
#include "src/Backend/Network/communication.h"
#include "src/Backend/backendDelegate.h"
#include "src/Backend/Network/communicationThread.h"

#include <thread>
#include <chrono>
#include <future>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //home w;
    home::getInstance()->setWindowTitle("Omegacam");
    QPalette homeP;
    homeP.setColor(QPalette::Window, primaryBackgroundColor);
    home::getInstance()->setAutoFillBackground(true);
    home::getInstance()->setPalette(homeP);
    home::getInstance()->show();
    //w.rightScrollArea->widget();

    auto backend = std::async(std::launch::async, [&] {
        backendDelegate::start();
        });

    auto communication = std::async(std::launch::async, [&] {
        communicationThread::start();
        });

    return a.exec();
}
