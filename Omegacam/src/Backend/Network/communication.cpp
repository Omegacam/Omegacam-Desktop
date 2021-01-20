#include "communication.h"

communication* communication::obj;

communication* communication::getInstance(){
    if (communication::obj == nullptr){
        communication::obj = new communication();
    }
    return communication::obj;
}

int communication::receive(){
    return 1;
}

communication::communication(){
    /*try {
        qInfo()
    }  catch (int e) {
       qInfo() << "error e caught: " << e;
    }*/

}

communication::~communication(){}
