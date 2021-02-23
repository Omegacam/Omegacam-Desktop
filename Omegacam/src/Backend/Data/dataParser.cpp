#include "dataManager.h"

cameraDataPacket dataManager::parseData(string& rawDataString) {

	//logs::stat("packet raw data - " + rawDataString);

	JS::ParseContext ctx(formatJSONString(rawDataString));

	cameraDataPacket packet;
	ctx.parseTo(packet);

	//logs::stat("packet data - " + packet.deviceName + " : " + packet.localIp);
	//logs::stat("packet #" + to_string(packet.frameNumber));

	return packet;
}

string dataManager::formatJSONString(string raw) { // removes backslash from json string
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] == '\\') {
			raw.erase(i, 1);
			i--;
		}
	}
	//logs::stat("formatted json - " + raw);
	return raw;
}
