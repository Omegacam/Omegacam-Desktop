#include "discoveryCommunication.h"

discoveryCommunication* discoveryCommunication::obj = nullptr;

discoveryCommunication* discoveryCommunication::getInstance() {
	if (discoveryCommunication::obj == nullptr) {
		discoveryCommunication::obj = new discoveryCommunication();
	}
	return obj;
}

discoveryCommunication::discoveryCommunication() {
	socket = new udpsocket();
	if (!connect(socketConnectionAddress, socketConnectionPort)) {
		logs::crit("UNABLE TO CONNECT DISCOVERY SOCKET");
	}
}

discoveryCommunication::~discoveryCommunication() {
	if (socket) {
		delete socket;
	}
}

//

bool discoveryCommunication::getSocketConnected() {
	return isSocketConnected;
}

bool discoveryCommunication::recv(socketbuffer& s_buffer) {
	if (!isSocketConnected) {
		logs::stat("socket not connected yet");
		return false;
	}
	return socket->recv(s_buffer);
}

bool discoveryCommunication::connect(string address, quint16 port) {
    if (isSocketConnected) {
        logs::crit("Socket already connected. Cannot connect to - " + address + ":" + to_string(port));
        return false;
    }
    return (isSocketConnected = socket->connect_socket(address, port));
}

bool discoveryCommunication::disconnect() {
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
