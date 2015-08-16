#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>

class GameObject
{
public:
	GameObject();
	GameObject(const char* filename);
	//copy constructor
	GameObject(const GameObject& orig);
	//copy assignment
	virtual GameObject& operator=(const GameObject& orig);
	//move constructor
	GameObject(GameObject && orig)noexcept : m_sprite(orig.m_sprite), m_x(orig.m_x), m_y(orig.m_y)
	{
		orig.m_sprite=nullptr;
		orig.m_x = -1;
		orig.m_y = -1;
	}
	//move assignment
	virtual GameObject& operator=(GameObject&& orig)
	{
		if (&orig != this)
		{
			m_sprite = std::move(orig.m_sprite);
			m_x = orig.m_x;
			m_y = orig.m_y;
		}
		return *this;
	}

	virtual ~GameObject();
	float getX()const { return m_x; }
	float getY()const { return m_y; }
	virtual void update() const = 0;
private:
	std::shared_ptr<ALLEGRO_BITMAP*> m_sprite;
	float m_x = 0;
	float m_y = 0;
};
#endif
