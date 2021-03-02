#ifndef _BACKEND_DELEGATE_H_
#define _BACKEND_DELEGATE_H_

#include "../common_includes.h"

class backendDelegate {
public:
	static void start();
	static void stop();

	static void updateDataBuffer(string data);

private:
	static bool isRunning; // to stop this thread from running after the main thread terminates

	static string dataBuffer;
	static bool hasRecvDataBuffer;

	static void parsedDataCallback(cameraDataPacket& data); // uses the parsed data and calls UI functions
};

#endif // !_BACKEND_DELEGATE_H_
