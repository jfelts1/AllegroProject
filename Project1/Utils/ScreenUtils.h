#ifndef SCREENUTILS_H
#define SCREENUTILS_H
#pragma once
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480
#include <cmath>
#include "../Point.h"
namespace Utils
{
	extern void screenWrap(Point& p);
}

#endif
