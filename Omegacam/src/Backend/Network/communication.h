#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "../../common_includes.h"
#include "Sockets/subSocket.h"
#include <zmq.h>

class communication
{
public:
    static communication* getInstance();
    //

    subsocket* createSocket();
    

private:
    communication();
    ~communication();
    static communication* obj;
    //
    
    void* ctx = nullptr;
    //void* sub = nullptr;
    void printVersion();

};

#endif // _COMMUNICATION_H_
