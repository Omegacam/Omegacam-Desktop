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
    zmq_close(dish);
    zmq_term(ctx);
}

//

void communication::printVersion() {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    logs::stat("zmq version - " + to_string(major) + "." + to_string(minor) + "." + to_string(patch));
    logs::stat("zmq has draft - " + to_string(zmq_has("draft")));
}

void communication::setupSocket() {
    if (!isSocketSetup) {
        dish = zmq_socket(ctx, ZMQ_DISH);
        /*int rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
        if (rc == -1) {
            logs::crit("Failed to set sock option subscribe");
            return;
        }*/
        //int t = 1;
        //int rc = zmq_setsockopt(dish, ZMQ_CONFLATE, &t, sizeof(t));
    }
    isSocketSetup = true;
}


bool communication::connect(string s) {
    if (!isSocketConnected) {
        int rc = zmq_bind(dish, s.c_str());
        if (rc == -1) {
            logs::crit("Failed to bind - " + s);
        }
        else {
            isSocketConnected = true;
            socketConnectionAddress = s;
        }

        rc = zmq_join(dish, "telemetry");
        if (rc == -1) {
            logs::crit("Failed to join group telemetry");
        }

        return rc != -1;
    }
    else {
        logs::crit("Socket already connected. Cannot connect to - " + s);
        return false;
    }
}

bool communication::disconnect() {
    if (isSocketConnected) {
        int rc = zmq_unbind(dish, socketConnectionAddress.c_str());
        if (rc == -1) {
            logs::crit("Failed to unbind - " + socketConnectionAddress);
        }
        else {
            isSocketConnected = false;
            socketConnectionAddress = "";
        }
        return rc != -1;
    }
    else {
        logs::stat("Socket doesn't have an active connection already");
        return true;
    }
}

bool communication::recv(string& buf) {
    if (isSocketConnected) {
        zmq_msg_t msg;
        int rc = zmq_msg_init(&msg);
        if (rc == -1) {
            return false;
        }
        rc = zmq_msg_recv(&msg, dish, ZMQ_NOBLOCK);
        if (rc == -1) {
            return false;
        }
        buf = string(static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
        zmq_msg_close(&msg);
        return true;
    }
    else {
        return false;
    }
}
