#ifndef INC_FLASHLIGHT_RGB_H_
#define INC_FLASHLIGHT_RGB_H_

#include "main.h"
#include "flashlight_input.h"
#include "flashlight.h"

typedef struct FL_RGB_Color {
	uint8_t r, g, b;
} FL_RGB_Color;

typedef struct FL_RGB {
	FlashLight flR, flG, flB;
	FL_RGB_Color color;
} FL_RGB;

void FL_RGB_Init(FL_RGB* rgb, Light rl_, Light gl_, Light bl_, TIM_HandleTypeDef* tim_);
void FL_RGB_TIMCB(FL_RGB* rgb, TIM_HandleTypeDef* htim);
void FL_RGB_PulseCB(FL_RGB* rgb, TIM_HandleTypeDef* htim);
void FL_RGB_Update(FL_RGB* rgb);
void FL_RGB_SetColor(FL_RGB* rgb, FL_RGB_Color color_);
void FL_RGB_SetColori(FL_RGB* rgb, uint8_t r_, uint8_t g_, uint8_t b_);
#endif // def INC_FLASHLIGHT_RGB_H_
