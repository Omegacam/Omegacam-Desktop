#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "../../common_includes.h"
#include "../backendStructs.h"
#include <json_struct.h>

class dataManager {
public:
	static dataManager* getInstance();
	// 

	void parseData(string& rawDataString);

private:
	dataManager();
	~dataManager();
	static dataManager* obj;
	//
};

#endif // !_DATA_MANAGER_H_
