#include "dataManager.h"

cameraDataPacket dataManager::parseData(string& rawDataString) {

	//logs::stat("packet raw data - " + rawDataString);

	JS::ParseContext ctx(rawDataString);

	cameraDataPacket packet;
	ctx.parseTo(packet);

	logs::stat("packet data - " + packet.deviceName + " : " + packet.localIp);

	return packet;
}

string dataManager::formatJSONString(string raw) { // removes backslash from json string
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] == '\\') {
			raw.erase(i, 1);
			i--;
		}
	}
	return raw;
}
