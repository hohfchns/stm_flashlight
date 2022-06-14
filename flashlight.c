#include "flashlight.h"
#include "flashlight_sm.h"
#include "flashlight_types.h"
#include "main.h"
#include <stdio.h>


void FL_Init(FlashLight *target, int blinkDuration_, int brightness_, Button button_, Light light_, TIM_HandleTypeDef* tim_)
{
	target->blinkDuration = blinkDuration_;
	target->blinkTime = 0;
	target->brightness = brightness_;
	target->state = FL_STATE_OFF;
	target->brightnessCounter = 0;
	target->brightnessTime = 0;
	target->triggerButton = button_;
	target->targetLight = light_;
	target->tim = tim_;
	target->lastTime = 0;

	__HAL_TIM_SET_AUTORELOAD(tim_, FL_TIM_TOLERANCE);
}

void FL_Update(FlashLight *target) {
	if (target->blinkTime >= target->blinkDuration)
	{
		__FL_Timeout_Blink(target);
	}
	else if (target->brightnessTime >= BRIGHTNESS_TOLERANCE)
	{
		__FL_Timeout_Brightness(target);
	}

	switch (target->state) {
	case FL_STATE_ON:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
		break;

	case FL_STATE_OFF:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
		break;

	case FL_STATE_LOW:
		// Counter increases in timeout
		if (target->brightnessCounter < 0)
		{
			printf("Brightness counter should not be under 0!\r\n");
			return;
		}

		if (target->brightnessCounter >= target->brightness) // Counter reached brightness
		{
			HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
		}
		else // Counter between 0 and brightness
		{
			HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
		}

		break;

	case FL_STATE_BLINK:
		// Logic is just in timeout
		break;

	default:
		break;
	}
}

void FL_SetState(FlashLight *target, FlashLightState state) {
	FLSM_SetState(&target->state, state);
	__HAL_TIM_SET_COUNTER(target->tim, 0);
}

void FL_SetBrightness(FlashLight *target, int brightness_) {
	target->brightness = brightness_;
	target->brightnessCounter = 0;
	__HAL_TIM_SET_COUNTER(target->tim, 0);
}

void FL_TIMCB(FlashLight* target, TIM_HandleTypeDef* triggerTim)
{
  if (!(target->tim == triggerTim))
  {
    return;
  }

  target->blinkTime += FL_TIM_TOLERANCE;
  target->brightnessTime += FL_TIM_TOLERANCE;
  return;

  if (target->state == FL_STATE_BLINK || target->state == FL_STATE_LOW)
  {
    HAL_GPIO_TogglePin(target->targetLight.GPIOx, target->targetLight.pin);
    target->brightnessCounter = (target->brightnessCounter + 1) % MAX_BRIGHTNESS_COUNT;
  }
}

void FL_BTNCB(FlashLight* target, uint16_t GPIO_Pin)
{
  if (GPIO_Pin == target->triggerButton.pin)
  {
      FLSM_SwitchState(&(target->state));
      __HAL_TIM_SET_COUNTER(target->tim, 0);
  }
}


void __FL_Timeout_Blink(FlashLight* target)
{
	target->blinkTime = 0;
	if (target->state == FL_STATE_BLINK)
	{
		HAL_GPIO_TogglePin(target->targetLight.GPIOx, target->targetLight.pin);
	}
}

void __FL_Timeout_Brightness(FlashLight* target)
{
	target->brightnessTime = 0;
	if (target->state == FL_STATE_LOW)
	{
		target->brightnessCounter = (target->brightnessCounter + 1) % MAX_BRIGHTNESS_COUNT;
	}
}





