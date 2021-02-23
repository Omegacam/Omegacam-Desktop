#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "../../common_includes.h"
#include "udp_socket.h"

class communication
{
public:
    static communication* getInstance();
    //

    bool connect(string address, quint16 port); // address
    bool disconnect(); // address

    void startThread();
    void stopThread();

    //bool recv(string& buf);

private:
    communication();
    ~communication();
    static communication* obj;
    //

    bool isRunningThread = false;

    //

    udpsocket* socket;
    bool isSocketConnected = false;
    
    string socketConnectionAddress = "";
    quint16 socketConnectionPort = 0;

};

#endif // _COMMUNICATION_H_
