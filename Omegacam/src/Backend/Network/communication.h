#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "../../common_includes.h"
#include <zmq.h>

class communication
{
public:
    static communication* getInstance();
    //

    bool addConnection(string s); // address
    bool removeConnection(string s); // address
    bool recv(string& buf);

private:
    communication();
    ~communication();
    static communication* obj;
    void printVersion();
    //
    
    void setupSocket();
    bool isSocketSetup = false;
    set<string> connectedAddresses; // stores addresses connceted by the socket

    void* ctx = nullptr;
    void* sub = nullptr;
   

};

#endif // _COMMUNICATION_H_
