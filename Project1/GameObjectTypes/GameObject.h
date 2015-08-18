#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <map>
#include <string>
#include "../SpriteUtils.h"

class GameObject
{
public:
	GameObject(const char* filename = "Images/test.bmp",float x = 0, float y = 0, float rotation = 0);
	//copy constructor
	GameObject(const GameObject& orig);
	//copy assignment
	virtual GameObject& operator=(const GameObject& orig);
	//move constructor
	GameObject(GameObject && orig)noexcept : m_sprite(orig.m_sprite), m_x(orig.m_x), m_y(orig.m_y), m_rotation(orig.m_rotation)
	{
		orig.m_sprite=nullptr;
		orig.m_x = -1;
		orig.m_y = -1;
		orig.m_rotation = 0;
	}
	//move assignment
	virtual GameObject& operator=(GameObject&& orig)
	{
		if (&orig != this)
		{
			m_sprite = std::move(orig.m_sprite);
			m_x = orig.m_x;
			m_y = orig.m_y;
			m_rotation = orig.m_rotation;
		}
		return *this;
	}

	virtual ~GameObject();
	float getX()const { return m_x; }
	float getY()const { return m_y; }
	//in radians
	float getRotation()const { return m_rotation; }
	virtual void update() const = 0;
	virtual void render() const = 0;
protected:
	ALLEGRO_BITMAP* m_sprite;
	float m_x = 0;
	float m_y = 0;
	//in radians
	float m_rotation = 0;
};
#endif
