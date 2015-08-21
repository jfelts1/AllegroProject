#ifndef SHIP_H
#define SHIP_H
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <map>
#include <string>
#include "GameObject.h"
#include "../SpriteUtils.h"
#include "../Point.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#define SHIP_HEIGHT 20
#define SHIP_WIDTH 10
#define P1X trans1.m[0][0]
#define P1Y trans1.m[0][1]
#define P2X trans2.m[0][0]
#define P2Y trans2.m[0][1]
#define P3X trans3.m[0][0]
#define P3Y trans3.m[0][1]
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

class Ship
	:public GameObject
{
public:
	Ship(float x = 0, float y = 0, float rotation = 0) :GameObject(x,y,rotation)
	{
		p1.x = pos.x;
		p1.y = pos.y - (SHIP_HEIGHT / 2);

		p2.x = pos.x - (SHIP_WIDTH / 2);
		p2.y = pos.y + (SHIP_HEIGHT / 2);

		p3.x = pos.x + (SHIP_WIDTH / 2);
		p3.y = pos.y + (SHIP_HEIGHT / 2);

		orig1.m[0][0] = p1.x - SCREEN_SIZE_X / 2;
		orig1.m[0][1] = p1.y - SCREEN_SIZE_Y / 2;
		orig2.m[0][0] = p2.x - SCREEN_SIZE_X / 2;
		orig2.m[0][1] = p2.y - SCREEN_SIZE_Y / 2;
		orig3.m[0][0] = p3.x - SCREEN_SIZE_X / 2;
		orig3.m[0][1] = p3.y - SCREEN_SIZE_Y / 2;

		P1X = p1.x - SCREEN_SIZE_X / 2;
		P1Y = p1.y - SCREEN_SIZE_Y / 2;

		P2X = p2.x - SCREEN_SIZE_X / 2;
		P2Y = p2.y - SCREEN_SIZE_Y / 2;

		P3X = p3.x - SCREEN_SIZE_X / 2;
		P3Y = p3.y - SCREEN_SIZE_Y / 2;
	}

	Ship(Point p, float rotation = 0) : GameObject(p,rotation)
	{
	}
	virtual ~Ship() {}

	//copy constructor
	Ship(const Ship& orig);
	//copy assignment
	Ship& operator=(const Ship& orig);
	//move constructor
	Ship(Ship&& orig) noexcept:p1(orig.p1), p2(orig.p2), p3(orig.p3), GameObject(*this)
	{
		orig.p1 = 0;
		orig.p2 = 0;
		orig.p3 = 0;
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

	void setRotationTarget(Point p);

	virtual void update() override;
	virtual void render() const override;

private:
	ALLEGRO_TRANSFORM trans1;
	ALLEGRO_TRANSFORM trans2;
	ALLEGRO_TRANSFORM trans3;
	ALLEGRO_TRANSFORM orig1;
	ALLEGRO_TRANSFORM orig2;
	ALLEGRO_TRANSFORM orig3;
	//point that make up the shape of the ship
	Point p1, p2, p3;
	//position to rotate towards
	Point m_mousePos;
};
#endif
