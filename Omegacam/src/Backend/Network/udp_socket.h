#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>
#include "../../common_includes.h"

struct socketbuffer {
	QHostAddress addr;
	quint16 addrport;
	QByteArray buffer;
};

class udpsocket : public QObject {
	Q_OBJECT
public:
	udpsocket(QObject* parent = 0); // default constructor
	void send(QByteArray data);
	bool connect_socket(string address, quint16 port);
	bool recv(socketbuffer& recvbuffer);
protected:
	QUdpSocket* socket;
	QHostAddress connected_addr;
	quint16 connected_addrport;
	socketbuffer recvbuffer;
};

#endif // !_UDP_SOCKET_H_