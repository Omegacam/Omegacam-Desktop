#ifndef _DISCOVERY_COMMUNICATION_H_
#define _DISCOVERY_COMMUNICATION_H_

#include "../../../common_includes.h"

#include "../Sockets/udp_socket.h"

class discoveryCommunication {
public:
	static discoveryCommunication* getInstance();
	//

	bool getSocketConnected();
	bool recv(socketbuffer& s_buffer);

	bool reconnect(string address, quint16 port); // to choose a new recv multicast address

private:
	discoveryCommunication();
	~discoveryCommunication();

	static discoveryCommunication* obj;
	//

	bool connect(string address, quint16 port);
	bool disconnect();

	//
	udpsocket* socket;
	bool isSocketConnected = false;

	const string socketConnectionAddress = "224.1.1.1";
	const quint16 socketConnectionPort = 5555;

};

#endif // !_DISCOVERY_COMMUNICATION_H_
