#include "Asteroid.h"

void Asteroid::updateHook()
{
	pos = pos + m_vect;
}

bool Asteroid::destroyCondition()
{
	return false;
}

void Asteroid::render() const
{
	al_draw_bitmap(m_sprite, pos.x, pos.y, 0);
}

void Asteroid::debugRender() const
{
}
