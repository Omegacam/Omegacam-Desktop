#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#include <QObject>
#include <QUdpSocket>
#include "../../common_includes.h"

struct socketbuffer {
	QHostAddress addr;
	quint16 addrport;
	QByteArray buffer;
};

class udpsocket : public QObject {
	Q_OBJECT
public:
	udpsocket(std::string address, quint16 port, QObject* parent = 0);
	void send(QByteArray data);
signals:
private slots:
	void recv();
protected:
	QUdpSocket* socket;
	QHostAddress connected_addr;
	quint16 connected_addrport;
	socketbuffer recvbuffer;
};

#endif // !_UDP_SOCKET_H_