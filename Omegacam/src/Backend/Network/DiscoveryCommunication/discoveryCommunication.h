#ifndef _DISCOVERY_COMMUNICATION_H_
#define _DISCOVERY_COMMUNICATION_H_

#include "../../../common_includes.h"

#include "../Sockets/udp_socket.h"

class discoveryCommunication {
public:
	static discoveryCommunication* getInstance();
	//

	bool getSocketConnected();


private:
	discoveryCommunication();
	~discoveryCommunication();

	static discoveryCommunication* obj;
	//

	bool connect(string address, quint16 port);

	//
	udpsocket* socket;
	bool isSocketConnected = false;

	string socketConnectionAddress = "224.1.1.1";
	quint16 socketConnectionPort = 5555;

};

#endif // !_DISCOVERY_COMMUNICATION_H_
