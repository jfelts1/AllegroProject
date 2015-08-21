#include "GameObject.h"

GameObject::GameObject(float x, float y, float rotation,const char* filename)
{
	m_sprite = Utils::getSprite(filename);
	pos.x = x;
	pos.y = y;
	m_rotation = rotation;
}

GameObject::GameObject(Point p, float rotation, const char * filename)
{
	m_sprite = Utils::getSprite(filename);
	pos = p;
	m_rotation = rotation;
}

//copy constructor
GameObject::GameObject(const GameObject & orig)
{
	m_sprite = orig.m_sprite;
	pos.x = orig.pos.x;
	pos.y = orig.pos.y;
	m_rotation = orig.m_rotation;
}

//copy assignment
GameObject & GameObject::operator=(const GameObject & orig)
{
	if (&orig != this)
	{
		m_sprite = orig.m_sprite;
		pos.x = orig.pos.x;
		pos.y = orig.pos.y;
		m_rotation = orig.m_rotation;
	}
	return *this;
}

GameObject::~GameObject()
{
}
