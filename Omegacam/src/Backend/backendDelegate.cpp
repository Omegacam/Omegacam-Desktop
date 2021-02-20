#include "backendDelegate.h"

#include "Network/communication.h"
#include "Data/dataManager.h"
#include "backendStructs.h"
#include <thread>
#include <chrono>

#include "../UI/home.h"

bool backendDelegate::isRunning = false;

void backendDelegate::start() {
	isRunning = true;
	communication::getInstance()->connect("tcp://192.168.1.9:1234");
	auto startT = std::chrono::high_resolution_clock::now();
	long c = 0;
	while (isRunning) {
		string rawDataString;
		if (communication::getInstance()->recv(rawDataString)) {
			//logs::stat(rawDataString);
			
			parsedDataCallback(dataManager::getInstance()->parseData(rawDataString));
			
			c++;
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			if (duration >= 1000000) { // 1 sec
				logs::stat( to_string(c) + " packets in 1 sec");
				startT = std::chrono::high_resolution_clock::now();
				c = 0;
			}
		}
		else {
			logs::stat("recv error");
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}

void backendDelegate::parsedDataCallback(cameraDataPacket& data) { // calls ui func with data from packet
	home::getInstance()->displayBase64Frame(data.frameData);
}
