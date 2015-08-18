#include "GameObject.h"

GameObject::GameObject(const char* filename,float x, float y, float rotation)
{
	m_sprite = Utils::getSprite(filename);
	m_x = x;
	m_y = y;
	m_rotation = rotation;
}

//copy constructor
GameObject::GameObject(const GameObject & orig)
{
	m_sprite = orig.m_sprite;
	m_x = orig.m_x;
	m_y = orig.m_y;
	m_rotation = orig.m_rotation;
}

//copy assignment
GameObject & GameObject::operator=(const GameObject & orig)
{
	if (&orig != this)
	{
		m_sprite = orig.m_sprite;
		m_x = orig.m_x;
		m_y = orig.m_y;
		m_rotation = orig.m_rotation;
	}
	return *this;
}

GameObject::~GameObject()
{
}
