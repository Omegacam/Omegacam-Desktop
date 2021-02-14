#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "../../common_includes.h"
#include <zmq.h>

class communication
{
public:
    static communication* getInstance();
    //

    bool connect(string s); // address
    bool disconnect(); // address
    
    bool recv(string& buf);

private:
    communication();
    ~communication();
    static communication* obj;
    void printVersion();
    //
    
    void setupSocket();
    bool isSocketSetup = false;
    bool isSocketConnected = false;
    string socketConnectionAddress = "";
    //set<string> connectedAddresses; // stores addresses connceted by the socket

    void* ctx = nullptr;
    void* sub = nullptr;

};

#endif // _COMMUNICATION_H_
