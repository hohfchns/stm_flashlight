#ifndef INC_FLASHLIGHT_TYPES_H_
#define INC_FLASHLIGHT_TYPES_H_

#include "main.h"
#include "flashlight_input.h"

typedef enum FlashLightState {
  FL_STATE_OFF = 0,
  FL_STATE_ON,
  FL_STATE_LOW,
  FL_STATE_BLINK,
  FL_STATE_INVALID
} FlashLightState;

typedef struct FlashLight {
  FlashLightState state;
  int blinkDuration;
  int brightness;
  int brightnessCounter;
  Button triggerButton;
  Light targetLight;
  TIM_HandleTypeDef* tim;
} FlashLight;

#endif /* INC_FLASHLIGHT_TYPES_H_ */
