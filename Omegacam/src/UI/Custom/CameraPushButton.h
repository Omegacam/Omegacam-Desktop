#ifndef _CAMERA_PUSH_BUTTON_H_
#define _CAMERA_PUSH_BUTTON_H_

#include <QPushButton>
#include "../../Backend/backendStructs.h"

class CameraPushButton : public QPushButton {
public:
	discoveryDataPacket discoveryData;
};

#endif // !_CAMERA_PUSH_BUTTON_H_

