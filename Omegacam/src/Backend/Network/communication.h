#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "../../common_includes.h"

class communication
{
public:
    static communication* getInstance();
    int receive();
private:
    communication();
    ~communication();
    static communication* obj;
};

#endif // _COMMUNICATION_H_
