#include "discoveryCommunicationThread.h"
#include "discoveryCommunication.h"

bool discoveryCommunicationThread::isRunning = false;

void discoveryCommunicationThread::start() {
	isRunning = true;

	while (isRunning) {

		if (discoveryCommunication::getInstance()->getSocketConnected()) {
			socketbuffer s_buffer;
			while (discoveryCommunication::getInstance()->recv(s_buffer)) {

				string rawData(s_buffer.buffer, s_buffer.buffer.size());

				logs::stat("recv multicast - " + rawData);

			}
		}

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void discoveryCommunicationThread::stop() {
	isRunning = false;
}