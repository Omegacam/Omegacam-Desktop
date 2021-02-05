#include "backendDelegate.h"

#include "Network/communication.h"
#include <msgpack.hpp>
#include <thread>
#include <chrono>

bool backendDelegate::isRunning = false;

void backendDelegate::start() {
	isRunning = true;
	communication::getInstance()->connect("tcp://192.168.1.6:1234");
	while (isRunning) {
		string a;
		if (communication::getInstance()->recv(a)) {
			logs::stat(a);
		}
		else if (zmq_errno() == 11){
			logs::stat("no msg recved");
		}
		else {
			logs::stat("msg error - " + to_string(zmq_errno()));
		}
		this_thread::sleep_for(chrono::milliseconds(300));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}
