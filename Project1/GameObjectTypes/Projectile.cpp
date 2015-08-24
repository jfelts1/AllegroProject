#include "Projectile.h"

void Projectile::updateHook()
{
	pos = pos + m_vect;
	m_lifetime++;
}

void Projectile::render() const
{
	al_draw_pixel(pos.x, pos.y, WHITE);
}

void Projectile::debugRender() const
{

}

bool Projectile::destroyCondition()
{
	if (m_lifetime < MAX_LIFETIME)
	{
		return false;
	}
	return true;
}
