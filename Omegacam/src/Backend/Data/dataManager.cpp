#include "dataManager.h"

dataManager::dataManager() {}
dataManager::~dataManager() {}

dataManager* dataManager::obj = nullptr;

dataManager* dataManager::getInstance() {
	if (dataManager::obj == nullptr) {
		dataManager::obj = new dataManager();
	}
	return dataManager::obj;
}

void dataManager::parseData(string& rawDataString) {

	JS::ParseContext ctx(rawDataString);

	cameraDataPacket packet;
	ctx.parseTo(packet);

	logs::stat("packet data - " + packet.s);
}

