#include "flashlight_commands.h"
#include "flashlight_sm.h"
#include "flashlight.h"
#include <stdio.h>
#include <string.h>

#define FL_CMD_MAX_SIZE 128

int FL_COMMANDS(const char* cmdbuffer, FlashLight* flashLight)
{
  #define COMM(command) strcmp(cmd, command) == 0
  char cmd[FL_CMD_MAX_SIZE];
  int maxCount;

  int paramc = sscanf(cmdbuffer, "%s %d", cmd, &maxCount);

  if (paramc == 0)
  {
    return 0;
  }

  if (COMM("full"))
  {
    printf("Setting LED state to ON\r\n");
    FL_SetState(flashLight, FL_STATE_ON);
  }
  else if (COMM("half"))
  {
    printf("Setting LED state to LOW\r\n");
    FL_SetState(flashLight, FL_STATE_LOW);
  }
  else if (COMM("blink"))
  {
    printf("Setting LED state to BLINK\r\n");
    FL_SetState(flashLight, FL_STATE_BLINK);
  }
  else if (COMM("off"))
  {
    printf("Setting LED state to OFF\r\n");
    FL_SetState(flashLight, FL_STATE_OFF);
  }
  else if (COMM("brightness") || COMM("br"))
  {
	  if (paramc < 2)
	  {
		  printf("Please provide an argument for brightness!\r\n");
		  return 1;
	  }
	  else if (maxCount < 0 || maxCount > MAX_BRIGHTNESS_COUNT)
	  {
		  printf("Brightness should be a number between 0 and %d!\r\n", MAX_BRIGHTNESS_COUNT);
		  return 1;
	  }

	  printf("Setting brightness to value %d\r\n\r", maxCount);
	  flashLight->brightness = maxCount;
  }
  else
  {
	  // Didn't get a valid command
	  return 0;
  }

  // Got a valid command
  return 1;
}
