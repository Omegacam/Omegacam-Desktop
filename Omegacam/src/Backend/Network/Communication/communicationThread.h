#ifndef _COMMUNICATION_THREAD_H_
#define _COMMUNICATION_THREAD_H_

#include "../../../common_includes.h"

#include <chrono>
#include <thread>

class communicationThread {
public:
	static void start();
	static void stop();
private:
	static bool isRunning;
};

#endif // !_COMMUNICATION_THREAD_H_
