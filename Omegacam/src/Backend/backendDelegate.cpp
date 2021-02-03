#include "backendDelegate.h"

#include "Network/communication.h"
#include <thread>
#include <chrono>

bool backendDelegate::isRunning = false;

void backendDelegate::start() {
	isRunning = true;
	subsocket* pub = communication::getInstance()->createSocket();
	pub->bind("tcp://192.168.1.11:1234");
	pub->subscribe("");
	while (isRunning) {
		string a;
		if (pub->recv(a)) {
			qInfo() << "received msg- " << QString::fromStdString(a);
		}
		else {
			qInfo() << "no msg recved - " << zmq_errno();
		}
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	delete pub;
	/*zmq::context_t ctx(1);
	zmq::socket_t sub(ctx, ZMQ_SUB);
	sub.connect("tcp://192.168.1.10:1234");
	sub.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	while (isRunning) {
		zmq::message_t msg;
		sub.recv(&msg, int(zmq::recv_flags::dontwait));
		qInfo() << "recvd: " << QString::fromStdString(string(static_cast<char*>(msg.data()), msg.size())) << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}*/

}

void backendDelegate::stop() {
	isRunning = false;
}