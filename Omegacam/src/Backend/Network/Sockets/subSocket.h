#ifndef _SUB_SOCKET_H_
#define _SUB_SOCKET_H_

#include "../../../common_includes.h"
#include <zmq.h>

class subsocket {
public:
	subsocket(void* ctx);
	~subsocket();
	bool bind(string s);
	bool unbind();
	bool subscribe(string topic);
	bool unsubscribe();
	
	//template <typename T>
	bool recv(string& buf);
private:
	void* sub;
	string address, topic;
};

#endif // !_SUB_SOCKET_H_
