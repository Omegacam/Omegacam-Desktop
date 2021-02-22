#ifndef _BACKEND_STRUCTS_H_
#define _BACKEND_STRUCTS_H_

#include <string>
#include <json_struct.h>

struct cameraDataPacket {
    std::string deviceName, localIp;
    
    int v_width, v_height;
    
    std::string frameData; // base64 encoded jpg
    int frameDataSize;

    quint64 frameNumber;

    JS_OBJ(deviceName, localIp, v_width, v_height, frameData, frameDataSize, frameNumber);
};

#endif // !_BACKEND_STRUCTS_H_
