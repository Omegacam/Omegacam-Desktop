#include "udp_socket.h"

//https://www.bogotobogo.com/Qt/Qt5_QUdpSocket.php

udpsocket::udpsocket(std::string address, quint16 port, QObject* parent) : QObject(parent) {
	socket = new QUdpSocket(this);
	
    // The most common way to use QUdpSocket class is 
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address, 
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
	
	connected_addr = QHostAddress(QString::fromStdString(address));
	connected_addrport = port;
	socket->bind(connected_addr, connected_addrport);
	
	connect(socket, SIGNAL(recv()), this, SLOT(recv()));
}

void udpsocket::send(QByteArray data) {
	// Sends the datagram datagram 
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram, 
    //                      const QHostAddress & host, quint16 port)
	socket->writeDatagram(data, connected_addr, connected_addrport);
}

void udpsocket::recv() {
	QByteArray buffer;
	buffer.resize(socket->pendingDatagramSize());

	QHostAddress senderaddress;
	quint16 senderport;

	// qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize, 
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data. 
    // The sender's host address and port is stored in *address and *port 
    // (unless the pointers are 0).

	socket->readDatagram(buffer.data(), buffer.size(), &senderaddress, &senderport);


	qInfo() << "Data recv: " << buffer;
	/*recvbuffer.addr = senderaddress;
	recvbuffer.addrport = senderport;
	recvbuffer.buffer = buffer;*/
}



