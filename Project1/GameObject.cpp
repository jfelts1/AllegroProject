#include "GameObject.h"

GameObject::GameObject()
{
	m_sprite = std::make_shared<ALLEGRO_BITMAP*>(al_load_bitmap("Images/test.bmp"));
}

GameObject::GameObject(const char* filename)
{
	m_sprite = std::make_shared<ALLEGRO_BITMAP*>(al_load_bitmap(filename));
}

//copy constructor
GameObject::GameObject(const GameObject & orig)
{
	m_sprite = orig.m_sprite;
	m_x = orig.m_x;
	m_y = orig.m_y;
}

//copy assignment
GameObject & GameObject::operator=(const GameObject & orig)
{
	if (&orig != this)
	{
		m_sprite = orig.m_sprite;
		m_x = orig.m_x;
		m_y = orig.m_y;
	}
	return *this;
}

GameObject::~GameObject()
{
}
