#ifndef SHIP_H
#define SHIP_H
#pragma once
#define SHIP_HEIGHT 20
#define SHIP_WIDTH 10

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <map>
#include <string>
#include "../SpriteUtils.h"
#include "../Point.h"
#include <allegro5/allegro_primitives.h>
class Ship
{
public:
	Ship(float x = 0, float y = 0, float rotation = 0)  
	{
		pos.x = x;
		pos.y = y;
		m_rotation = rotation;
	}

	Ship(Point p, float rotation = 0)
	{
		pos = p;
		m_rotation = rotation;
	}
	virtual ~Ship() {}

	//copy constructor
	Ship(const Ship& orig);
	//copy assignment
	Ship& operator=(const Ship& orig);
	//move constructor
	Ship(Ship&& orig) noexcept:p1(orig.p1), p2(orig.p2), p3(orig.p3), pos(orig.pos), m_rotation(orig.m_rotation)
	{
		orig.m_rotation = 0;
		orig.p1 = 0;
		orig.p2 = 0;
		orig.p3 = 0;
		orig.pos = 0;
	}
	//move assignment
	Ship& operator=(Ship&& orig)
	{
		if (this != &orig)
		{
			p1 = orig.p1;
			p2 = orig.p2;
			p3 = orig.p3;
			pos = orig.pos;
			m_rotation = orig.m_rotation;
			orig.m_rotation = 0;
			orig.p1 = 0;
			orig.p2 = 0;
			orig.p3 = 0;
			orig.pos = 0;
		}
		return *this;
	}

	void update();
	void render()const;

private:
	//point that make up the shape of the ship
	Point p1, p2, p3;
	//the ship's position relative to the gameworld origin
	Point pos;
	//the ship's rotation in radians
	float m_rotation = 0;
};
#endif
