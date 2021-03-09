#ifndef _DISCOVERY_COMMUNICATION_THREAD_H_
#define _DISCOVERY_COMMUNICATION_THREAD_H_

#include "../../common_includes.h"

#include <chrono>
#include <thread>

class discoveryCommunicationThread {
public:
	static void start();
	static void stop();
private:
	static bool isRunning;
};

#endif // !_DISCOVERY_COMMUNICATION_THREAD_H_
