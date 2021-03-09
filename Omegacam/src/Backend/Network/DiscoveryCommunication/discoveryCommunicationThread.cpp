#include "discoveryCommunicationThread.h"
#include "discoveryCommunication.h"

bool discoveryCommunicationThread::isRunning = false;

void discoveryCommunicationThread::start() {
	isRunning = true;

	while (isRunning) {

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void discoveryCommunicationThread::stop() {
	isRunning = false;
}