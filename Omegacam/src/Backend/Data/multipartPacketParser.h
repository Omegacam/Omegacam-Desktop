#ifndef _MULTIPART_PACKET_PARSER_H_
#define _MULTIPART_PACKET_PARSER_H_

#include "../../common_includes.h"

struct packetData {
	int packet_group_id, group_packet_size, group_packet_num;
	string rawData;
};

#define MULTIPART_MAX_BUFFER_SIZE 1024

class multipartPacketParser {
public:
	static void input(string& rawPacketData);
private:
	static vector<vector<string>> buffer;
	
	//

	static packetData parseRawData(string rawPacketData);
	static void sortPacketData(packetData& packet);
	static string assemblePacket(int packet_group_id);

	//

	static bool isPacketReady(int packet_group_id);
	static void clearBuffer();

	//
		
	static void callCallback(string& data);
};

#endif // !_MULTIPART_PACKET_PARSER_H_
