#ifndef INC_FLASHLIGHT_RGB_H_
#define INC_FLASHLIGHT_RGB_H_

#include "flashlight_input.h"

typedef struct FL_RGB {
	FlashLight r, g, b;
} FL_RGB;

void FL_RGB_Init(FL_RGB* rgb, Light rl_, Light gl_, Light bl_);

#endif // def INC_FLASHLIGHT_RGB_H_
