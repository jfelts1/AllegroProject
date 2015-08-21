#include "Ship.h"

Ship::Ship(const Ship& orig)
{
	if (this != &orig)
	{
		p1 = orig.p1;
		p2 = orig.p2;
		p3 = orig.p3;
		pos = orig.pos;
		m_rotation = orig.m_rotation;
	}
}

Ship & Ship::operator=(const Ship & orig)
{
	if (this != &orig)
	{
		p1 = orig.p1;
		p2 = orig.p2;
		p3 = orig.p3;
		pos = orig.pos;
		m_rotation = orig.m_rotation;
	}
	return *this;
}

void Ship::update()
{
	p1.x = pos.x;
	p1.y = pos.y - (SHIP_HEIGHT / 2);

	p2.x = pos.x - (SHIP_WIDTH / 2);
	p2.y = pos.y + (SHIP_HEIGHT / 2);

	p3.x = pos.x + (SHIP_WIDTH / 2);
	p3.y = pos.y + (SHIP_HEIGHT / 2);
}

void Ship::render() const
{
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	al_draw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, white, 0);
}
