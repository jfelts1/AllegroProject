#include "Asteroid.h"

void Asteroid::updateHook()
{
	pos = pos + m_vect;
	m_rotation = fmod(m_rotation + m_rotationRate, 2 * PI);
}

bool Asteroid::destroyCondition()
{
	for (auto obj : GameObjects)
	{
		if (collisionCheck(obj.get()))
		{
			asteroidCount--;
			obj->hitBy(this);
			return true;
		}
	}
	return false;
}

void Asteroid::render() const
{
	al_draw_rotated_bitmap(m_sprite, m_spriteHeight/2, m_spriteWidth/2, pos.x, pos.y, m_rotation, 0);
}

void Asteroid::debugRender() const
{
}

#if _WIN32
#pragma warning(disable: 4100)
#endif
void Asteroid::hitBy(const GameObject * other)
{

}
#if _WIN32
#pragma warning(default: 4100)
#endif
