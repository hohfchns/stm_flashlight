#include "flashlight_rgb_commands.h"
#include <stdio.h>
#include <string.h>

#define FL_CMD_MAX_SIZE 128

int FL_RGB_COMMANDS(const char* cmdbuffer, FL_RGB* rgb)
{
  #define COMM(command) strcmp(cmd, command) == 0
  char cmd[FL_CMD_MAX_SIZE];
  int rgbArg[3];

  int paramc = sscanf(cmdbuffer, "%s %d %d %d", cmd, rgbArg, rgbArg+1, rgbArg+2);

  if (paramc == 0)
  {
	return 0;
  }

  if (COMM("rgb") || COMM("color") || COMM("c"))
  {
	  if (paramc < 4)
	  {
		  printf("Please supply enough args for rgb!\r\n");
		  return 0;
	  }

	  FL_RGB_SetColori(rgb, rgbArg[0], rgbArg[1], rgbArg[2]);
  }
  else
  {
	  // Didn't get a valid command
	  return 0;
  }

  // Got a valid command
  return 1;
}
