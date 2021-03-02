#include "communicationThread.h"
#include "communication.h"

#include "../backendDelegate.h"

bool communicationThread::isRunning = false;

void communicationThread::start() {
	isRunning = true;
	
	if (!communication::getInstance()->connect("tcp://192.168.1.9:1234")) {
		isRunning = false;
		logs::crit("COULD NOT CONNECT WITH SOCKET");
		return;
	}
	
	auto startT = std::chrono::high_resolution_clock::now();
	long c = 0;

	while (isRunning) {

		string rawDataString;
		if (communication::getInstance()->recv(rawDataString)) {
			//logs::stat(rawDataString);

			//dataManager::getInstance()->parseData(rawDataString);

			backendDelegate::updateDataBuffer(rawDataString);

			c++;
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			if (c == 30) {
				logs::stat("30 FRAMES = " + to_string(duration) + " microseconds");
				startT = std::chrono::high_resolution_clock::now();
				c = 0;
			}

		}
		else if (zmq_errno() == 11) {
			//	logs::stat("no msg recved");
		}
		else {
			logs::stat("msg error - " + to_string(zmq_errno()));
		}

		this_thread::sleep_for(chrono::microseconds(1));
	}

}

void communicationThread::stop() {
	isRunning = false;
}