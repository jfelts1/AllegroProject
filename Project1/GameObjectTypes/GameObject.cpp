#include "GameObject.h"

GameObject::GameObject(float x, float y, float rotation, Owner own,const char* filename)
{
	m_sprite = Utils::getSprite(filename);
	m_spriteHeight = al_get_bitmap_height(m_sprite);
	m_spriteWidth = al_get_bitmap_width(m_sprite);
	pos.x = x;
	pos.y = y;
	m_rotation = rotation;
	m_collisionRadius = (m_spriteHeight + m_spriteWidth) / 2;
	m_own = own;
}

GameObject::GameObject(Point p, float rotation, Owner own, const char * filename)
{
	m_sprite = Utils::getSprite(filename);
	m_spriteHeight = al_get_bitmap_height(m_sprite);
	m_spriteWidth = al_get_bitmap_width(m_sprite);
	pos = p;
	m_rotation = rotation;
	m_collisionRadius = (m_spriteHeight + m_spriteWidth) / 2;
	m_own = own;
}

//copy constructor
GameObject::GameObject(const GameObject & orig)
{
	m_sprite = orig.m_sprite;
	m_spriteHeight = orig.m_spriteHeight;
	m_spriteWidth = orig.m_spriteWidth;
	pos.x = orig.pos.x;
	pos.y = orig.pos.y;
	m_rotation = orig.m_rotation;
}

//copy assignment
GameObject & GameObject::operator=(const GameObject& orig)
{
	if (&orig != this)
	{
		m_sprite = orig.m_sprite;
		m_spriteHeight = orig.m_spriteHeight;
		m_spriteWidth = orig.m_spriteWidth;
		pos.x = orig.pos.x;
		pos.y = orig.pos.y;
		m_rotation = orig.m_rotation;
	}
	return *this;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	updateHook();
	Utils::screenWrap(pos);
}

bool GameObject::collisionCheck(const GameObject* other)
{
	if (this != other)
	{
		if (hypotf(this->getX() - other->getX(), this->getY() - other->getY()) < this->getCollisionRadius())
		{
			//std::cout <<typeid(*this).name()<<" collided with "<<typeid(*other).name()<< std::endl;
			printf("%s(%.1f,%.1f) collided with %s(%.1f,%.1f)\n", typeid(*this).name(),this->getX(),this->getY(), typeid(*other).name(),other->getX(),other->getY());
			return true;
		}
	}
	return false;
}
