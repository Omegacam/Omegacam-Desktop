#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "../../common_includes.h"
#include <json_struct.h>

class dataManager {
public:
	static dataManager* getInstance();
	// 

	cameraDataPacket parseToCameraStruct(string& rawDataString);

private:
	dataManager();
	~dataManager();
	static dataManager* obj;
	//

	string formatJSONString(string raw);

};

#endif // !_DATA_MANAGER_H_
