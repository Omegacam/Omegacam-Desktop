#include "discoveryCommunicationThread.h"
#include "discoveryCommunication.h"

#include "../../backendDelegate.h"

bool discoveryCommunicationThread::isRunning = false;

void discoveryCommunicationThread::start() {
	isRunning = true;

	while (isRunning) {

		if (discoveryCommunication::getInstance()->getSocketConnected()) {
			
			vector<string> b;

			socketbuffer s_buffer;
			while (discoveryCommunication::getInstance()->recv(s_buffer)) {

				b.push_back(string(s_buffer.buffer, s_buffer.buffer.size()));
				//logs::stat("recv multicast - " + rawData);
			}
			
			if (b.size()) {
				backendDelegate::updateDiscoveryData(b);
			}

		}

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void discoveryCommunicationThread::stop() {
	isRunning = false;
}