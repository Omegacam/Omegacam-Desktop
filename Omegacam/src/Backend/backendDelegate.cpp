#include "backendDelegate.h"

#include "Network/communication.h"
#include "Data/dataManager.h"
#include "backendStructs.h"
#include <thread>
#include <chrono>

#include "../UI/home.h"
#include "Data/multipartPacketParser.h"

bool backendDelegate::isRunning = false;

//

string backendDelegate::rawDataBuffer = "";
bool backendDelegate::hasReceivedRawDataBuffer = false;

//

string backendDelegate::parsedDataBuffer = "";
bool backendDelegate::hasReceivedParsedDataBuffer = false;

//


void backendDelegate::updateRawDataBuffer(string dataString) {
	rawDataBuffer = dataString;
	hasReceivedRawDataBuffer = true;
}

void backendDelegate::updateParsedDataBuffer(string dataString) {
	parsedDataBuffer = dataString;
	hasReceivedParsedDataBuffer = true;
}


void backendDelegate::start() {
	isRunning = true;
	
	
	auto startT = std::chrono::high_resolution_clock::now();
	long c = 0;
	quint64 maxFrame = 0;

	while (isRunning) {
		if (hasReceivedRawDataBuffer) {
		

			multipartPacketParser::input(rawDataBuffer);

			hasReceivedRawDataBuffer = false;
			rawDataBuffer = "";
		}

		if (hasReceivedParsedDataBuffer) {

			//logs::stat("recv full data packet");

			parsedDataCallback(dataManager::getInstance()->parseToCameraStruct(parsedDataBuffer));

			hasReceivedParsedDataBuffer = false;
			parsedDataBuffer = "";
		}
		

		this_thread::sleep_for(chrono::microseconds(1));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}

void backendDelegate::parsedDataCallback(cameraDataPacket& data) { // calls ui func with data from packet
	if (data.frameData != "") {
		home::getInstance()->displayBase64Frame(data.frameData);
	}
	else {
		logs::stat("invalid frame data in callback");
	}
}
