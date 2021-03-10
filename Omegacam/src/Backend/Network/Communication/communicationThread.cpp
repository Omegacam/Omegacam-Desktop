#include "communicationThread.h"
#include "communication.h"

#include "../../backendDelegate.h"

bool communicationThread::isRunning = false;

void communicationThread::start() {
	isRunning = true;
	
	if (!communication::getInstance()->connect("tcp://192.168.1.9:5000")) {
		isRunning = false;
		logs::crit("COULD NOT CONNECT WITH SOCKET");
		return;
	}

	while (isRunning) {

		string rawDataString;
		if (communication::getInstance()->recv(rawDataString)) {
			//logs::stat(rawDataString);

			//dataManager::getInstance()->parseData(rawDataString);

			backendDelegate::updateCameraDataBuffer(rawDataString);
		
		}
		else if (zmq_errno() != 11){
			logs::stat("msg error - " + to_string(zmq_errno()));
		}

		this_thread::sleep_for(chrono::microseconds(1));
	}

}

void communicationThread::stop() {
	isRunning = false;
}