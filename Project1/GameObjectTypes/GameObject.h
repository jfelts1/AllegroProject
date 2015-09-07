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
#include <cstdio>
#include <vector>
#include <typeinfo>
#include "../Utils/SpriteUtils.h"
#include "../Utils/ScreenUtils.h"
#include "../Utils/PhysicsUtils.h"
#include "../Utils/FileUtils.h"
#include "../Point.h"
#include "../Vector.h"

enum Owner
{
	Player,
	World
};

class GameObject
{
public:
	GameObject(float x = 0, float y = 0, float rotation = 0, Owner own = World,const char* filename = "Images/Null.png");
	GameObject(Point p, float rotation = 0, Owner = World, const char* filename = "Images/Null.png");
	//copy constructor
	GameObject(const GameObject& orig);
	//copy assignment
	virtual GameObject& operator=(const GameObject& orig);
	//move constructor
	GameObject(GameObject && orig)noexcept : m_sprite(orig.m_sprite),m_spriteHeight(orig.m_spriteHeight),m_spriteWidth(orig.m_spriteWidth), pos(orig.pos), m_rotation(orig.m_rotation)
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
			m_spriteHeight = orig.m_spriteHeight;
			m_spriteWidth = orig.m_spriteWidth;
			pos.x = orig.pos.x;
			pos.y = orig.pos.y;
			m_rotation = orig.m_rotation;
		}
		return *this;
	}

	virtual ~GameObject();
	float getX()const { return pos.x; }
	float getY()const { return pos.y; }
	float getCollisionRadius()const { return m_collisionRadius; }
	Owner getOwner()const { return m_own; }
	//in radians
	float getRotation()const { return m_rotation; }
	void update();
	virtual void updateHook() {}
	virtual bool destroyCondition() = 0;
	virtual void render() const = 0;
	virtual void debugRender() const = 0;
	virtual void hitBy(const GameObject* other) = 0;
	bool collisionCheck(const GameObject* other);
protected:
	ALLEGRO_BITMAP* m_sprite;
	int m_spriteHeight = 0;
	int m_spriteWidth = 0;
	float m_collisionRadius = 0;
	//the objects's position relative to the gameworld origin
	Point pos;
	//the objects's rotation in radians
	float m_rotation = 0;
	//the objects's movement vector
	Utils::Vector m_vect;
	Owner m_own;
};

extern std::vector<std::shared_ptr<GameObject>> GameObjects;

#endif
