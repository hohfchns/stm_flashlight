#include "flashlight_sm.h"
#include "main.h"

FlashLightState FLSM_SetState(FlashLightState* state, FlashLightState desired)
{
	*state = desired;

	return *state;
}

FlashLightState FLSM_SwitchState(FlashLightState* state)
{
  switch (*state)
  {
    case FL_STATE_OFF:
      FLSM_SetState(state, FL_STATE_ON);
      break;

    case FL_STATE_ON:
      FLSM_SetState(state, FL_STATE_LOW);
      break;

    case FL_STATE_LOW:
      FLSM_SetState(state, FL_STATE_BLINK);
      break;

    case FL_STATE_BLINK:
      FLSM_SetState(state, FL_STATE_OFF);
      break;

    default:
      return FL_STATE_INVALID;
      break;
  }

  return *state;
}
