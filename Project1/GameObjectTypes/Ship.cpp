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

//set the movment vector member
void Ship::setSpeedTarget(int key)
{
	if (key == MOVE_FORWARD)
	{
		m_vect.setY(m_vect.getY() - SHIP_ACELLERATION*sin(m_rotation + PI / 2));
		m_vect.setX(m_vect.getX() - SHIP_ACELLERATION*cos(m_rotation + PI / 2));
	}
	if (key == MOVE_BACK)
	{
		m_vect.setY(m_vect.getY() + SHIP_ACELLERATION*sin(m_rotation + PI / 2));
		m_vect.setX(m_vect.getX() + SHIP_ACELLERATION*cos(m_rotation + PI / 2));
	}
	if (key == MOVE_LEFT)
	{
		m_vect.setY(m_vect.getY() - SHIP_ACELLERATION*sin(m_rotation));
		m_vect.setX(m_vect.getX() - SHIP_ACELLERATION*cos(m_rotation));
	}
	if (key == MOVE_RIGHT)
	{
		m_vect.setY(m_vect.getY() + SHIP_ACELLERATION*sin(m_rotation));
		m_vect.setX(m_vect.getX() + SHIP_ACELLERATION*cos(m_rotation));
	}

	//prevent accelerating faster than the max speed
	if (m_vect.getMagnitude() > MAX_SHIP_SPEED)
	{
		float ratio = MAX_SHIP_SPEED / m_vect.getMagnitude();
		m_vect.setY(m_vect.getY()*ratio);
		m_vect.setX(m_vect.getX()*ratio);
	}
}

void Ship::update()
{
	m_rotation = atan2f(pos.y - m_mousePos.y, pos.x - m_mousePos.x)- PI/2;
	//update ship position
	pos = pos + m_vect;
	al_copy_transform(&trans1, &orig1);
	al_copy_transform(&trans2, &orig2);
	al_copy_transform(&trans3, &orig3);
	al_rotate_transform(&trans1, m_rotation);
	al_rotate_transform(&trans2, m_rotation);
	al_rotate_transform(&trans3, m_rotation);

	transformShipPointsToWorldCoords();
	Utils::screenWrap(pos);
}

void Ship::render() const
{
	al_draw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, WHITE, 0);
}

void Ship::debugRender() const
{
	al_draw_filled_rectangle(pos.x + 1, pos.y + 1, pos.x - 1, pos.y - 1, RED);
}
