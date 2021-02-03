#include "communication.h"

communication* communication::obj;

communication* communication::getInstance(){
    if (communication::obj == nullptr){
        communication::obj = new communication();
    }
    return communication::obj;
}
communication::communication(){
    printVersion();
    ctx = zmq_ctx_new();
}

communication::~communication(){
    zmq_term(ctx);
}

//

void communication::printVersion() {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    qInfo() << "version - " << major << "." << minor << "." << patch << endl;
}


subsocket* communication::createSocket() {
    subsocket* s = new subsocket(ctx);
    /*bool f = 1;
    f = f && s->bind(address);
    f = f && s->subscribe(topic);
    if (!f) {
        qCritical() << "bind or subscribe failed when creating socket";
    }*/
    return s;
}


