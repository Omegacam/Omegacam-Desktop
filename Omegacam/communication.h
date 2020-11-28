#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "common_includes.h"

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

#endif // COMMUNICATION_H
