#ifndef _BACKEND_STRUCTS_H_
#define _BACKEND_STRUCTS_H_

#include <string>
#include <json_struct.h>

struct cameraDataPacket {
    std::string s;

    JS_OBJ(s);
};

#endif // !_BACKEND_STRUCTS_H_
