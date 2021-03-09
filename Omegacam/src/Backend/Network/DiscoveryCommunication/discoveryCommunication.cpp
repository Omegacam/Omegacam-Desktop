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
	/*if (!connect(socketConnectionAddress, socketConnectionPort)) {
		logs::crit("UNABLE TO CONNECT DISCOVERY SOCKET");
	}*/	
}

discoveryCommunication::~discoveryCommunication() {
	delete socket;
}

bool discoveryCommunication::getSocketConnected() {
	return isSocketConnected;
}

bool discoveryCommunication::connect(string address, quint16 port) {
    /*if (isSocketConnected) {
        logs::crit("Socket already connected. Cannot connect to - " + address + ":" + to_string(port));
        return false;
    }
    return (isSocketConnected = socket->connect_socket(address, port));*/
	return 0;
}
