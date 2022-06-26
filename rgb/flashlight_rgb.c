#include "flashlight_rgb.h"

void FL_RGB_Init(FL_RGB* rgb, Light rl_, Light gl_, Light bl_, TIM_HandleTypeDef* tim_)
{
	Button tmp = { 0, 0 };
	FL_RGB_SetColori(rgb, 5, 5, 5);

	FL_Init(&rgb->flR, 500, rgb->color.r, tmp, rl_, tim_);
	FL_Init(&rgb->flG, 500, rgb->color.g, tmp, gl_, tim_);
	FL_Init(&rgb->flB, 500, rgb->color.b, tmp, bl_, tim_);

	rgb->flR.targetLight = rl_;
	// Blue and green have flipped order in pins
	rgb->flG.targetLight = gl_;
	rgb->flB.targetLight = bl_;

	FL_Settings(&rgb->flR, 255);
	FL_Settings(&rgb->flG, 255);
	FL_Settings(&rgb->flB, 255);

	FL_RGB_SetColori(rgb, 255, 60, 125);
}

void FL_RGB_TIMCB(FL_RGB* rgb, TIM_HandleTypeDef* htim)
{
	FL_TIMCB(&rgb->flR, htim);
	FL_TIMCB(&rgb->flG, htim);
	FL_TIMCB(&rgb->flB, htim);
}

void FL_RGB_Update(FL_RGB* rgb)
{
	rgb->flR.state = FL_STATE_LOW;
	rgb->flG.state = FL_STATE_LOW;
	rgb->flB.state = FL_STATE_LOW;

	rgb->flR.brightness = rgb->color.r;
	rgb->flG.brightness = rgb->color.g;
	rgb->flB.brightness = rgb->color.b;

	FL_Update(&rgb->flR);
	FL_Update(&rgb->flG);
	FL_Update(&rgb->flB);
}

void FL_RGB_SetColor(FL_RGB* rgb, FL_RGB_Color color_)
{
	rgb->color = color_;
}

void FL_RGB_SetColori(FL_RGB* rgb, uint8_t r_, uint8_t g_, uint8_t b_)
{
	rgb->color.r = r_;
	rgb->color.g = g_;
	rgb->color.b = b_;
}



