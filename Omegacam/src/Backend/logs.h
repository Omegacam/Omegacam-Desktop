#ifndef _LOGS_H_
#define _LOGS_H_

#include <QDebug>
#include <string>

class logs {
public:
	static void crit(std::string s); // critical
	static void stat(std::string s); // status
private:	
};

#endif // !_LOGS_H_
