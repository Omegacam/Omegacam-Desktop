#include "communication.h"
#include <zmq.hpp>

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
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    qInfo() << "version - " << major << "." << minor << "." << patch << endl;
}

communication::~communication(){}
