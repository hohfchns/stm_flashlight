#ifndef INC_FLASHLIGHT_INPUT_H_
#define INC_FLASHLIGHT_INPUT_H_

#include "main.h"

typedef struct Button {
  GPIO_TypeDef* GPIOx;
  uint16_t pin;
} Button;

typedef Button Light;

int BUTTON_GetOn(Button* button);


#endif /* INC_FLASHLIGHT_INPUT_H_ */
