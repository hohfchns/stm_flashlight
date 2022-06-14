#include "flashlight_rgb.h"


void FL_RGB_Init(FL_RGB* rgb, Light rl_, Light gl_, Light bl_)
{
	rgb->r.targetLight = rl_;
	rgb->g.targetLight = gl_;
	rgb->b.targetLight = bl_;
}
