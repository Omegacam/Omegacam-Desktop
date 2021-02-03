#include "logs.h"

void logs::crit(std::string s) {
	qCritical() << "CRITICAL: " << QString::fromStdString(s);
}

void logs::stat(std::string s) {
	qInfo() << "STATUS: " << QString::fromStdString(s);
}