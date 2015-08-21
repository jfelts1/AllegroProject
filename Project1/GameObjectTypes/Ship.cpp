#include "Ship.h"

Ship::Ship(const Ship& orig) :GameObject(*this)
{
	if (this != &orig)
	{
		p1 = orig.p1;
		p2 = orig.p2;
		p3 = orig.p3;
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

void Ship::setRotationTarget(Point p)
{
	m_mousePos = p;
}

void Ship::update()
{
	float angle = atan2f(pos.y - m_mousePos.y, pos.x - m_mousePos.x)- PI/2;
	al_copy_transform(&trans1, &orig1);
	al_copy_transform(&trans2, &orig2);
	al_copy_transform(&trans3, &orig3);
	al_rotate_transform(&trans1, angle);
	al_rotate_transform(&trans2, angle);
	al_rotate_transform(&trans3, angle);
	//printf("p1x: %f p1y: %f p2x: %f p2y: %f p3x: %f p3y: %f\n", P1X, P1Y, P2X, P2Y, P3X, P3Y);

	p1.x = P1X + pos.x;
	p1.y = P1Y + pos.y;

	p2.x = P2X + pos.x;
	p2.y = P2Y + pos.y;

	p3.x = P3X + pos.x;
	p3.y = P3Y + pos.y;
}

void Ship::render() const
{
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	al_draw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, white, 0);
}
