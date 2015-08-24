#ifndef POINT_H
#define POINT_T
#pragma once

#include <allegro5/allegro.h>
#include "Vector.h"
using Utils::Vector;

struct Point
{
	Point(float x = 0, float y = 0) 
	{
		this->x = x;
		this->y = y;
	}

	virtual ~Point() {}

	//copy constructor
	Point(const Point& orig)
	{
		if (this != &orig)
		{
			x = orig.x;
			y = orig.y;
		}
	}

	//copy assignment
	Point& operator=(const Point& orig)
	{
		if (this != &orig)
		{
			x = orig.x;
			y = orig.y;
		}
		return *this;
	}

	//move constructor
	Point(Point&& orig) noexcept: x(orig.x), y(orig.y)
	{
		orig.x = 0;
		orig.y = 0;
	}

	//move assignment
	Point& operator=(Point&& orig)
	{
		if (this != &orig)
		{
			x = orig.x;
			y = orig.y;
			orig.x = 0;
			orig.y = 0;
		}
		return *this;
	}

	//set both the x and y component to the given number
	Point& operator=(const float val)
	{
		x = val;
		y = val;
		return *this;
	}

	Point operator+(const Vector rhs)
	{
		Point ret(this->x + rhs.getX(), this->y + rhs.getY());
		return ret;
	}

	void getCurMousePos(ALLEGRO_MOUSE_EVENT mouse)
	{
		x = mouse.x;
		y = mouse.y;
	}

	float x = 0;
	float y = 0;
};
#endif
