#ifndef _BACKEND_STRUCTS_H_
#define _BACKEND_STRUCTS_H_

#include <string>
#include <json_struct.h>

struct cameraDataPacket {
    std::string deviceName, localIp;
    
    int v_width, v_height;
    
    std::string frameData; // base64 encoded jpg
    int frameDataSize;
    JS_OBJ(deviceName, localIp, v_width, v_height, frameData, frameDataSize);
};

struct discoveryDataPacket {
    std::string deviceName, cameraConnectionIP;
    quint32 cameraConnectionPort;

    JS_OBJ(deviceName, cameraConnectionIP, cameraConnectionPort);
};

#endif // !_BACKEND_STRUCTS_H_
