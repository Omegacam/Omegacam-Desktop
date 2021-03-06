#include "dataManager.h"

cameraDataPacket dataManager::parseCameraData(string& rawDataString) {

	JS::ParseContext ctx(rawDataString);

	cameraDataPacket packet;
	ctx.parseTo(packet);

	//logs::stat("packet data - " + packet.deviceName + " : " + packet.localIp);

	return packet;
}

discoveryDataPacket dataManager::parseDiscoveryData(string& rawDataString) {

	JS::ParseContext ctx(rawDataString);

	discoveryDataPacket packet;
	ctx.parseTo(packet);

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
