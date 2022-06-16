#ifndef INC_FLASHLIGHT_H_
#define INC_FLASHLIGHT_H_

#include "flashlight_types.h"
#include "main.h"
#include "flashlight_input.h"

#define BRIGHTNESS_TOLERANCE 10
#define MAX_BRIGHTNESS_COUNT 10
#define FL_TIM_TOLERANCE 10

void FL_Init(FlashLight *target, int blinkDuration_, int brightness_, Button button_, Light light_, TIM_HandleTypeDef* tim);
void FL_Update(FlashLight* target);
void FL_SetState(FlashLight* target, FlashLightState state);
void FL_SetBrightness(FlashLight* target, int brightness_);
void FL_TIMCB(FlashLight* target, TIM_HandleTypeDef* triggerTim);
void FL_BTNCB(FlashLight* target, uint16_t GPIO_Pin);
void FL_Settings(FlashLight* target, int brightnessMax_, int timMultiplier_);
void __FL_Timeout_Blink(FlashLight* target);
void __FL_Timeout_Brightness(FlashLight* target);

#endif /* INC_FLASHLIGHT_H_ */
