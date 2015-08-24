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
#include "../ColorDefines.h"
#include "../Keybinds.h"
#define SHIP_HEIGHT 30
#define SHIP_WIDTH 20
#define P1X trans1.m[0][0]
#define P1Y trans1.m[0][1]
#define P2X trans2.m[0][0]
#define P2Y trans2.m[0][1]
#define P3X trans3.m[0][0]
#define P3Y trans3.m[0][1]
#define MAX_SHIP_SPEED 10
#define SHIP_ACELLERATION 1
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

extern int MOVE_FORWARD;
extern int MOVE_LEFT;
extern int MOVE_RIGHT;
extern int MOVE_BACK;

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

		initTransforms(orig1,orig2,orig3);
		initTransforms(trans1, trans2, trans3);

		al_rotate_transform(&trans1, rotation);
		al_rotate_transform(&trans2, rotation);
		al_rotate_transform(&trans3, rotation);

		transformShipPointsToWorldCoords();
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
	Ship(Ship&& orig) noexcept: GameObject(*this),p1(orig.p1), p2(orig.p2), p3(orig.p3)
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
	void setSpeedTarget(int key);
	// Inherited via GameObject
	virtual void update() override;
	// Inherited via GameObject
	virtual void render() const override;
	// Inherited via GameObject
	virtual void debugRender() const override;

private:
	ALLEGRO_TRANSFORM trans1;
	ALLEGRO_TRANSFORM trans2;
	ALLEGRO_TRANSFORM trans3;
	ALLEGRO_TRANSFORM orig1;
	ALLEGRO_TRANSFORM orig2;
	ALLEGRO_TRANSFORM orig3;
	//point that makes up the shape of the ship
	Point p1, p2, p3;
	//position to rotate towards
	Point m_mousePos;

	inline void initTransforms(ALLEGRO_TRANSFORM& t1, ALLEGRO_TRANSFORM& t2, ALLEGRO_TRANSFORM& t3)
	{
		t1.m[0][0] = p1.x - pos.x;
		t1.m[0][1] = p1.y - pos.y;

		t2.m[0][0] = p2.x - pos.x;
		t2.m[0][1] = p2.y - pos.y;

		t3.m[0][0] = p3.x - pos.x;
		t3.m[0][1] = p3.y - pos.y;
	}

	inline void transformShipPointsToWorldCoords()
	{
		p1.x = P1X + pos.x;
		p1.y = P1Y + pos.y;

		p2.x = P2X + pos.x;
		p2.y = P2Y + pos.y;

		p3.x = P3X + pos.x;
		p3.y = P3Y + pos.y;
	}

	
};
#endif
