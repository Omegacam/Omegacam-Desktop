#include "multipartPacketParser.h"
#include "../backendDelegate.h"

vector<vector<string>> multipartPacketParser::buffer(MULTIPART_MAX_BUFFER_SIZE, vector<string>());

// public input func
void multipartPacketParser::input(string& rawPacketData) {
	packetData packet = parseRawData(rawPacketData);

	sortPacketData(packet);

	if (isPacketReady(packet.packet_group_id)) {
		callCallback(assemblePacket(packet.packet_group_id));
	}

}


// private internal funcs

packetData multipartPacketParser::parseRawData(string rawPacketData) {
	string data;
	vector<int> identifiers(3);
	
	string b;
	int c = 0;
	for (char i : rawPacketData) {
		if (i == '~') { // delimiter
			identifiers[c] = stoi(b);
			b = "";
			c++;
		}
		else {
			b += i;
		}
	}

	data = b;
	packetData d {identifiers[0], identifiers[1], identifiers[2], data};

	//logs::stat("data recv in packet: " + to_string(d.packet_group_id) + ":" + to_string(d.group_packet_size) + ":" + to_string(d.group_packet_num));
	
	return d;
}

void multipartPacketParser::sortPacketData(packetData& packet) { // takes the packet part and places it in the correct array
	if (buffer[packet.packet_group_id].size() == 0) {
		buffer[packet.packet_group_id] = vector<string>(packet.group_packet_size);
	}
	
	buffer[packet.packet_group_id][packet.group_packet_num] = packet.rawData;

}

bool multipartPacketParser::isPacketReady(int packet_group_id) { // checks if packet is ready to assemble
	for (string i : buffer[packet_group_id]) {
		if (i == "") {
			return false; // data is either not there or is corrupt
		}
	}
	return true;
}

string multipartPacketParser::assemblePacket(int packet_group_id) {
	string b = "";
	for (string i : buffer[packet_group_id]) {
		b += i;
	}

	// perform optional buffer cleanup here

	clearBuffer();

	//

	return b;
}


void multipartPacketParser::clearBuffer() {
	buffer = vector<vector<string>>(MULTIPART_MAX_BUFFER_SIZE, vector<string>());
}


// callback to ui functions
void multipartPacketParser::callCallback(string& data) {
	backendDelegate::updateParsedDataBuffer(data);
}
