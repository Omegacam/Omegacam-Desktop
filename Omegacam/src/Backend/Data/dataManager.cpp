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


