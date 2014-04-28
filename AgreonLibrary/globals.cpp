#include "globals.h"

cLog* Log = new cLog();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const char*	APP_NAME = "Reach The Surface";

int PLAYER_POINTS = 0;

const double PI = 3.14159265;

extern double tilt(double x1, double y1, double x2, double y2)
{ 
	return std::atan((y1 - y2) / (x1 - x2))*180/PI;
}

string itos( int number )
{
   stringstream ss;
   ss << number;
   return ss.str();
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if(y1 >= y2 + h2) return false;
    if(x1 >= x2 + w2) return false;
    if(y1 + h1 <= y2) return false;
    if(x1 + w1 <= x2) return false;

	return true;
}