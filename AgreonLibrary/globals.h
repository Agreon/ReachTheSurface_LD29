#pragma once

#include "cLog.h"

enum
{
	STATE_NULL,
	STATE_EXIT,
	STATE_INTRO,
	STATE_MENU,
	STATE_CREDITS,
	STATE_PROLOG,
	STATE_GAME,
	STATE_POINTS
};

extern cLog* Log;

extern const int	SCREEN_WIDTH;
extern const int	SCREEN_HEIGHT;

extern const char*	APP_NAME;

extern int PLAYER_POINTS;

extern const double PI;

extern double tilt(double x1, double y1, double x2, double y2);
extern string itos( int number );
extern bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);