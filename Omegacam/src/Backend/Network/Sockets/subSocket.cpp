#include "subSocket.h"

subsocket::subsocket(void* ctx) {
	void* sub = zmq_socket(ctx, ZMQ_SUB);
	if (sub == nullptr) {
		qCritical() << "nullptr in socket create";
	}
}

subsocket::~subsocket() {
	zmq_close(sub);
}

bool subsocket::bind(string s) {
	//sub.bind(s);
	int rc = zmq_bind(sub, s.c_str());
	if (rc == -1) {
		// handle error here
		qCritical() << "Failed to bind - " << zmq_errno();
		return false;
	}
	address = s;
	return true;
}

bool subsocket::unbind() {
	int rc = zmq_unbind(sub, address.c_str());
	if (rc == -1) {
		qCritical() << "Failed to unbind - " << zmq_errno();
		return false;
	}
	address = "";
	return true;
}

bool subsocket::subscribe(string t) {
	int rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, t.c_str(), t.length());
	if (rc == -1){
		qCritical() << "Failed to subscribe - " << zmq_errno();
		return false;
	}
	topic = t;
	return true;
}

bool subsocket::unsubscribe() {
	int rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
	if (rc == -1){
		qCritical() << "Failed to unsubscribe - " << zmq_errno() << endl;
		return false;
	}
	topic = "";
	return true;
}

//template <typename T>
bool subsocket::recv(string& buf) {
	//sub.recv(buf, len, int(zmq::recv_flags::dontwait));
	zmq_msg_t msg;
	int rc = zmq_msg_init(&msg);
	if (rc == -1) {
		return false;
	}
	//buf = string(static_cast<char*>(msg.data()), msg.size());
	rc = zmq_msg_recv(&msg, sub, 0);
	if (rc == -1) {
		return false;
	}
	buf = string(static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
	zmq_msg_close(&msg);
	return true;
}
