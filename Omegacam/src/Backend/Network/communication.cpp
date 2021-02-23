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

bool communication::connect(string address, quint16 port) {
    if (isSocketConnected) {
        logs::crit("Socket already connected. Cannot connect to - " + address + ":" + to_string(port));
        return false;
    }
    socket = new udpsocket();
    return (isSocketConnected = socket->connect_socket(address, port));
}

bool communication::disconnect() {
    if (isSocketConnected) {
        socket->disconnect();
        socket = nullptr;
        isSocketConnected = false;
    }
    else {
        logs::stat("Socket doesn't have an active connection already");
    }
    return true;
}

/*bool communication::recv(string& buf) { // now using callback to backendDelegate thread
    if (isSocketConnected) {
        //
        socketbuffer buffer;
        bool hasRecvData = socket->recv(buffer);

        buf = string(buffer.buffer, buffer.buffer.size());

        return hasRecvData;
    }
    else {
        logs::stat("Socket is not connected");
        return false;
    }
}*/
