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
	target->brightnessMax = MAX_BRIGHTNESS_COUNT;
	target->brightnessTime = 0;
	target->triggerButton = button_;
	target->targetLight = light_;
	target->tim = tim_;
	target->lastTime = 0;
	target->brightTimMultiplier = 1;
	target->timChannel = TIM_CHANNEL_1;

#ifdef FL_USE_PWM
	int onDuration = target->brightness * target->brightTimMultiplier * FL_TIM_TOLERANCE;
	__HAL_TIM_SET_COMPARE(target->tim, target->timChannel, onDuration);

	int offDuration = target->brightness * target->brightTimMultiplier * target->brightnessMax;
	__HAL_TIM_SET_AUTORELOAD(target->tim, offDuration);
#endif
#ifndef FL_USE_PWM
	__HAL_TIM_SET_AUTORELOAD(target->tim, FL_TIM_TOLERANCE);
#endif
}

void FL_Update(FlashLight *target) {
#ifndef FL_USE_PWM
	if (target->blinkTime >= target->blinkDuration)
	{
		__FL_Timeout_Blink(target);
	}
	else if (target->brightnessTime >= FL_TIM_TOLERANCE)
	{
		__FL_Timeout_Brightness(target);
	}
#endif // def FL_USE_PWM

	switch (target->state) {
	case FL_STATE_ON:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
		break;

	case FL_STATE_OFF:
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
		break;

	case FL_STATE_LOW:
		;
		// Counter increases in timeout
#ifdef FL_USE_PWM
		int onDuration = target->brightness * FL_TIM_TOLERANCE;
		__HAL_TIM_SET_COMPARE(target->tim, target->timChannel, onDuration);

		int offDuration = target->brightnessMax * FL_TIM_TOLERANCE;
		__HAL_TIM_SET_AUTORELOAD(target->tim, offDuration);
#endif

#ifndef FL_USE_PWM
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

#endif
		break;

	case FL_STATE_BLINK:
#ifdef FL_USE_PWM
		__HAL_TIM_SET_COMPARE(target->tim, target->timChannel, target->blinkDuration);
#endif
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

#ifdef FL_USE_PWM
  if (target->state == FL_STATE_LOW)
  {
	  __FL_Timeout_Brightness(target);
  }
  else if (target->state == FL_STATE_BLINK)
  {
	  __FL_Timeout_Blink(target);
  }
#endif

#ifndef FL_USE_PWM
  target->blinkTime += FL_TIM_TOLERANCE;
  target->brightnessTime += FL_TIM_TOLERANCE;
#endif // def FL_USE_PWM
  return;
}

void FL_PulseCB(FlashLight* target, TIM_HandleTypeDef* triggerTim)
{
	if (target->tim != triggerTim)
	{
		return;
	}

	if (target->state == FL_STATE_LOW)
	{
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 0);
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


void FL_Settings(FlashLight* target, int brightnessMax_, int timMultiplier_)
{
	target->brightnessMax = brightnessMax_;
	target->brightTimMultiplier = timMultiplier_;
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
#ifdef FL_USE_PWM
	if (target->state == FL_STATE_LOW)
	{
		HAL_GPIO_WritePin(target->targetLight.GPIOx, target->targetLight.pin, 1);
	}
#endif

#ifndef FL_USE_PWM
		target->brightnessCounter = (target->brightnessCounter + target->brightTimMultiplier) % target->brightnessMax;
#endif

}





