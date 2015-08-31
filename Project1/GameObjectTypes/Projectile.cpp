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

#if _WIN32
#pragma warning(disable: 4100)
#endif
void Projectile::hitBy(const GameObject * other)
{
	m_hit = true;
}
#if _WIN32
#pragma warning(default: 4100)
#endif

bool Projectile::destroyCondition()
{
	if (m_hit == true)
	{
		return true;
	}
	if (m_lifetime >= MAX_LIFETIME)
	{
		return true;
	}
	return false;
}
