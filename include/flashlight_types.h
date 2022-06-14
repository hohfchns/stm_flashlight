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
  uint32_t blinkTime;
  int brightness;
  int brightnessCounter;
  uint32_t brightnessTime;
  Button triggerButton;
  Light targetLight;
  TIM_HandleTypeDef* tim;

  uint32_t lastTime;
} FlashLight;

#endif /* INC_FLASHLIGHT_TYPES_H_ */
