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
			if (c == 30) {
				logs::stat("30 FRAMES = " + to_string(duration) + " microseconds");
				startT = std::chrono::high_resolution_clock::now();
				c = 0;
			}
		}
		else if (zmq_errno() == 11){
		//	logs::stat("no msg recved");
		}
		else {
			logs::stat("msg error - " + to_string(zmq_errno()));
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
