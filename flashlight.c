#include "flashlight.h"
#include "flashlight_sm.h"
#include "flashlight_types.h"
#include "main.h"
#include <stdio.h>


void FL_Init(FlashLight *target, int blinkDuration_, int brightness_, Button button_, Light light_, TIM_HandleTypeDef* tim_)
{
	target->state = FL_STATE_OFF;

	target->blinkDuration = blinkDuration_;
	target->brightness = brightness_;
	target->triggerButton = button_;
	target->targetLight = light_;
	target->lastTime = 0;

	MCL_Init(&target->brightnessClock, MAX_BRIGHTNESS_COUNT);
}

void FL_Update(FlashLight *target) {
	switch (target->state) {
	case FL_STATE_ON:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
		break;

	case FL_STATE_OFF:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
		break;

	case FL_STATE_LOW:
		if (target->brightnessClock.count >= target->brightness) // Counter reached brightness
		{
			HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
		}

		// Pull to reset the clock if it's timed out
		if (MCL_Pull(&target->brightnessClock) == MCL_STATE_TIMEOUT)
		{
			HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
		}

		break;

	case FL_STATE_BLINK:
		break;

	default:
		break;
	}
}

void FL_SetState(FlashLight *target, FlashLightState state) {
	FLSM_SetState(&target->state, state);
}

void FL_SetBrightness(FlashLight *target, int brightness_) {
	target->brightness = brightness_;
}

void FL_TIMCB(FlashLight* target, TIM_HandleTypeDef* triggerTim)
{
	MCL_CallBack_Timer(&target->brightnessClock);
}

void FL_BTNCB(FlashLight* target, uint16_t GPIO_Pin)
{
  if (GPIO_Pin == target->triggerButton.pin)
  {
      FLSM_SwitchState(&(target->state));
  }
}


void FL_SetBrightnessFromMax(FlashLight* target, int brightnessMax, int desired)
{
//	target->brightness = desired / brightnessMax;
}

void FL_Settings(FlashLight* target, int brightnessMax_)
{
	target->brightnessClock.maxCount = brightnessMax_;
	target->brightnessClock.timeScale = brightnessMax_ / MAX_BRIGHTNESS_COUNT;
//	target->brightnessClock.timeScale = timMultiplier_;
}





