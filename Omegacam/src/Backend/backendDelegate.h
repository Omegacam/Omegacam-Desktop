#ifndef _BACKEND_DELEGATE_H_
#define _BACKEND_DELEGATE_H_

#include "../common_includes.h"

class backendDelegate {
public:
	static void start();
	static void stop();

	static void updateRawDataBuffer(string dataString);
	static void updateParsedDataBuffer(string dataString);

private:
	//
	static string rawDataBuffer;
	static bool hasReceivedRawDataBuffer;
	//
	static string parsedDataBuffer;
	static bool hasReceivedParsedDataBuffer;


	static bool isRunning; // to stop this thread from running after the main thread terminates

	static void parsedDataCallback(cameraDataPacket& data); // uses the parsed data and calls UI functions
};

#endif // !_BACKEND_DELEGATE_H_
