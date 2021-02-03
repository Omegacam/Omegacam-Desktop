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
    setupSocket();
}

communication::~communication(){
    zmq_close(sub);
    zmq_term(ctx);
}

//

void communication::printVersion() {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    qInfo() << "version - " << major << "." << minor << "." << patch << endl;
}

void communication::setupSocket() {
    if (!isSocketSetup) {
        sub = zmq_socket(ctx, ZMQ_SUB);
        int rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
        if (rc == -1) {
            logs::crit("Failed to set sock option subscribe");
            return;
        }
    }
    isSocketSetup = true;
}


bool communication::addConnection(string s) {
    int rc = zmq_connect(sub, s.c_str());
    if (rc == -1) {
        logs::crit("Failed to bind - " + s);
    }
    else {
        connectedAddresses.insert(s);
    }
    return rc != -1;
}

bool communication::removeConnection(string s) {
    int rc = zmq_disconnect(sub, s.c_str());
    if (rc == -1) {
        logs::crit("Failed to unbind - " + s);
    }
    else {
        connectedAddresses.erase(s);
    }
    return rc != -1;
}

bool communication::recv(string& buf) {
    if (connectedAddresses.size() == 0){
        return false;
    }
    zmq_msg_t msg;
    int rc = zmq_msg_init(&msg);
    if (rc == -1) {
        return false;
    }
    rc = zmq_msg_recv(&msg, sub, ZMQ_DONTWAIT);
    if (rc == -1) {
        return false;
    }
    buf = string(static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
    zmq_msg_close(&msg);
    return true;
}
