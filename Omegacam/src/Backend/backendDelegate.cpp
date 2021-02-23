#include "backendDelegate.h"

#include "Network/communication.h"
#include "Data/dataManager.h"
#include "backendStructs.h"
#include <thread>
#include <chrono>

#include "../UI/home.h"

bool backendDelegate::isRunning = false;

//

string backendDelegate::rawDataBuffer = "";
bool backendDelegate::hasReceivedRawDataBuffer = false;

//

void backendDelegate::updateDataBuffer(string& dataString) {
	rawDataBuffer = dataString;
	hasReceivedRawDataBuffer = true;
}

void backendDelegate::start() {
	isRunning = true;
	
	
	auto startT = std::chrono::high_resolution_clock::now();
	long c = 0;
	quint64 maxFrame = 0;

	while (isRunning) {
		/*string rawDataString;
		if (communication::getInstance()->recv(rawDataString)) {
			//logs::stat(rawDataString);
			
			//parsedDataCallback(dataManager::getInstance()->parseData(rawDataString));
			
			//cameraDataPacket packet = dataManager::getInstance()->parseData(rawDataString);

			//maxFrame = max(maxFrame, packet.frameNumber);

			c++;
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			if (duration >= 1000000) { // 1 sec
				logs::stat( to_string(c) + " packets in 1 sec = " + to_string(maxFrame) + "th frame");
				startT = std::chrono::high_resolution_clock::now();
				c = 0;
			}
		}
		else {
			//logs::stat("recv error");
		}*/
		if (hasReceivedRawDataBuffer) {
			cameraDataPacket packet = dataManager::getInstance()->parseData(rawDataBuffer);
			
			//logs::stat("parsed frame #" + to_string(packet.frameNumber));
			/*c++;
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			if (duration >= 1000000) { // 1 sec
				logs::stat( to_string(c) + " packets in 1 sec");
				startT = std::chrono::high_resolution_clock::now();
				c = 0;
			}*/

			hasReceivedRawDataBuffer = false;
			rawDataBuffer = "";
		}
		this_thread::sleep_for(chrono::microseconds(1));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}

void backendDelegate::parsedDataCallback(cameraDataPacket& data) { // calls ui func with data from packet
	home::getInstance()->displayBase64Frame(data.frameData);
}
