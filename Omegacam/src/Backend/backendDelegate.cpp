#include "backendDelegate.h"

#include "Network/Communication/communication.h"
#include "Data/dataManager.h"
#include "backendStructs.h"
#include <thread>
#include <chrono>

#include <unordered_set>

#include "../UI/home.h"
#include "../UI/cameralistwidget.h"

bool backendDelegate::isRunning = false;

bool backendDelegate::hasRecvCameraDataBuffer = false;
string backendDelegate::cameraDataBuffer = "";

void backendDelegate::updateCameraDataBuffer(string data) {
	if (cameraDataBuffer == "") {
		cameraDataBuffer = data;
		hasRecvCameraDataBuffer = true;
	}
}

void backendDelegate::updateDiscoveryData(vector<string> data) {

	//logs::stat("before size - " + to_string(data.size()));

	unordered_set<string> d(begin(data), end(data));

	vector<discoveryDataPacket> v;

	for (string i : d) {
		v.push_back(dataManager::getInstance()->parseDiscoveryData(i));
	}

	parsedDiscoveryDataCallback(v);
}

void backendDelegate::start() {
	isRunning = true;

	while (isRunning) {
		if (hasRecvCameraDataBuffer) {

			parsedCameraDataCallback(dataManager::getInstance()->parseCameraData(cameraDataBuffer));

			hasRecvCameraDataBuffer = false;
			cameraDataBuffer = "";
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

void backendDelegate::stop() {
	isRunning = false;
}

void backendDelegate::parsedCameraDataCallback(cameraDataPacket& data) { // calls ui func with data from packet
	if (data.frameData != "") {
		home::getInstance()->displayBase64Frame(data.frameData);
	}
}

void backendDelegate::parsedDiscoveryDataCallback(vector<discoveryDataPacket>& data) {
	for (discoveryDataPacket i : data) {
		logs::stat("device name - " + i.deviceName + " - " + i.cameraConnectionIP + ":" + to_string(i.cameraConnectionPort));
	}

	home::getInstance()->getCameraListWidget()->updateList(data);

}
