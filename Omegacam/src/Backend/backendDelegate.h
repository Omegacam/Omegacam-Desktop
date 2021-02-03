#ifndef _BACKEND_DELEGATE_H_
#define _BACKEND_DELEGATE_H_

#include "../common_includes.h"

class backendDelegate {
public:
	static void start();
	static void stop();
private:
	static bool isRunning; // to stop this thread from running after the main thread terminates
};

#endif // !_BACKEND_DELEGATE_H_