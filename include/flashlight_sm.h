#ifndef INC_FLASHLIGHT_SM_H_
#define INC_FLASHLIGHT_SM_H_

#include "flashlight_types.h"

FlashLightState FLSM_SwitchState(FlashLightState* target);
FlashLightState FLSM_SetState(FlashLightState* state, FlashLightState desired);

#endif /* INC_FLASHLIGHT_SM_H_ */
