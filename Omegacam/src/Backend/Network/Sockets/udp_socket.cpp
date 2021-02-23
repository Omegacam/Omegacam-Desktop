#include "udp_socket.h"

//https://www.bogotobogo.com/Qt/Qt5_QUdpSocket.php

udpsocket::udpsocket(QObject* parent) : QObject(parent) {}

bool udpsocket::connect_socket(string address, quint16 port) {
	connected_addr = QHostAddress(QString::fromStdString(address));

	socket = new QUdpSocket(this);
	if (!socket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
		logs::crit("Failed to bind udp socket to port " + to_string(port));
		return false;
	}

	if (socket->state() != QAbstractSocket::BoundState) {
		logs::crit("Socket state is not in bound state");
		return false;
	}

	// need to join on an interface https://stackoverflow.com/questions/19218994/qt-joinmulticastgroup-for-all-interface
	// netsh interface ip show joins

	QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

	for (int i = 0; i < interfaceList.size(); i++) {
		QNetworkInterface current_interface = interfaceList.at(i);
		if (current_interface.isValid() && 
			current_interface.flags().testFlag(QNetworkInterface::CanMulticast) && 
			current_interface.flags().testFlag(QNetworkInterface::IsRunning) && 
			!current_interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

			if (!socket->joinMulticastGroup(connected_addr, current_interface)) {
				logs::crit("Failed to join udp socket multicast group " + address + " : " + socket->errorString().toUtf8().constData());
				return false;
			}
		
		}
	}

	//socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1);

	//logs::stat("success setup socket with address - " + address + ":" + to_string(port));
	//connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));

	return true;
}

void udpsocket::send(QByteArray data) { // unused function
	// Sends the datagram datagram 
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram, 
    //                      const QHostAddress & host, quint16 port)
	socket->writeDatagram(data, connected_addr, connected_addrport);
}

bool udpsocket::recv(socketbuffer& recvbuffer) {
	if (socket->hasPendingDatagrams()) {
		QByteArray raw_bytes;
		raw_bytes.resize(socket->pendingDatagramSize());

		QHostAddress senderaddress;
		quint16 senderport;

		// qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize, 
		//                 QHostAddress * address = 0, quint16 * port = 0)
		// Receives a datagram no larger than maxSize bytes and stores it in data. 
		// The sender's host address and port is stored in *address and *port 
		// (unless the pointers are 0).

		socket->readDatagram(raw_bytes.data(), raw_bytes.size(), &senderaddress, &senderport);

		//qInfo() << "recv data: " << raw_bytes;

		recvbuffer.addr = senderaddress;
		recvbuffer.addrport = senderport;
		recvbuffer.buffer = raw_bytes;
		return true;
	}
	else {
		//logs::stat("no data is to be recv'd");
		return false;
	}
}
