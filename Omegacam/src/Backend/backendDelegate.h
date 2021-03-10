#ifndef _BACKEND_DELEGATE_H_
#define _BACKEND_DELEGATE_H_

#include "../common_includes.h"

class backendDelegate {
public:
	static void start();
	static void stop();

	static void updateCameraDataBuffer(string data);
	static void updateDiscoveryData(vector<string> data);

private:
	static bool isRunning; // to stop this thread from running after the main thread terminates

	//

	static string cameraDataBuffer;
	static bool hasRecvCameraDataBuffer;

	//

	static void parsedCameraDataCallback(cameraDataPacket& data); // uses the parsed data and calls UI functions
	static void parsedDiscoveryDataCallback(vector<discoveryDataPacket>& data);
};

#endif // !_BACKEND_DELEGATE_H_
