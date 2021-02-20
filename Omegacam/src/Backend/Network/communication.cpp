#include "communication.h"

communication* communication::obj;

communication* communication::getInstance(){
    if (communication::obj == nullptr){
        communication::obj = new communication();
    }
    return communication::obj;
}
communication::communication(){
}

communication::~communication(){
}

//
void communication::setupSocket() {
    if (!isSocketSetup) {

    }
    isSocketSetup = true;
}


bool communication::connect(string s) {
    if (!isSocketConnected) {
        return true;
    }
    else {
        logs::crit("Socket already connected. Cannot connect to - " + s);
        return false;
    }
}

bool communication::disconnect() {
    if (isSocketConnected) {
    }
    else {
        logs::stat("Socket doesn't have an active connection already");
    }
    return true;
}

bool communication::recv(string& buf) {
    if (isSocketConnected) {
        
    }
    else {
        return false;
    }
}
