#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "../Utils/SpriteUtils.h"
#include "../Point.h"
#include "../Vector.h"
#include "../Utils/ScreenUtils.h"
#define PI 3.1415926535897932384626433832795
using std::vector;

class GameObject
{
public:
	GameObject(float x = 0, float y = 0, float rotation = 0,const char* filename = "Images/test.bmp");
	GameObject(Point p, float rotation = 0, const char* filename = "Images/test.bmp");
	//copy constructor
	GameObject(const GameObject& orig);
	//copy assignment
	virtual GameObject& operator=(const GameObject& orig);
	//move constructor
	GameObject(GameObject && orig)noexcept : m_sprite(orig.m_sprite), pos(orig.pos), m_rotation(orig.m_rotation)
	{
		orig.m_sprite=nullptr;
		orig.pos.x = -1;
		orig.pos.y = -1;
		orig.m_rotation = 0;
	}
	//move assignment
	virtual GameObject& operator=(GameObject&& orig)
	{
		if (&orig != this)
		{
			m_sprite = std::move(orig.m_sprite);
			pos.x = orig.pos.x;
			pos.y = orig.pos.y;
			m_rotation = orig.m_rotation;
		}
		return *this;
	}

	virtual ~GameObject();
	float getX()const { return pos.x; }
	float getY()const { return pos.y; }
	//in radians
	float getRotation()const { return m_rotation; }
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void debugRender() const = 0;
protected:
	ALLEGRO_BITMAP* m_sprite;
	//the objects's position relative to the gameworld origin
	Point pos;
	//the objects's rotation in radians
	float m_rotation = 0;
	//the objects's movement vector
	Utils::Vector m_vect;
};
#endif
