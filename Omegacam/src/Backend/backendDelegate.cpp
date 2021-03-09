#include "backendDelegate.h"

#include "Network/Communication/communication.h"
#include "Data/dataManager.h"
#include "backendStructs.h"
#include <thread>
#include <chrono>

#include "../UI/home.h"

bool backendDelegate::isRunning = false;

bool backendDelegate::hasRecvDataBuffer = false;
string backendDelegate::dataBuffer = "";

void backendDelegate::updateDataBuffer(string data) {
	if (dataBuffer == "") {
		dataBuffer = data;
		hasRecvDataBuffer = true;
	}
}

void backendDelegate::start() {
	isRunning = true;

	while (isRunning) {
		if (hasRecvDataBuffer) {

			parsedDataCallback(dataManager::getInstance()->parseCameraData(dataBuffer));

			hasRecvDataBuffer = false;
			dataBuffer = "";
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}

void backendDelegate::parsedDataCallback(cameraDataPacket& data) { // calls ui func with data from packet
	if (data.frameData != "") {
		home::getInstance()->displayBase64Frame(data.frameData);
	}
}
