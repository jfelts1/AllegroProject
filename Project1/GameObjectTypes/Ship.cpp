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

void Ship::moveFor()
{
	m_vect.setY(m_vect.getY() - SHIP_ACELLERATION*sin(m_rotation + PI / 2));
	m_vect.setX(m_vect.getX() - SHIP_ACELLERATION*cos(m_rotation + PI / 2));
}

void Ship::moveBack()
{
	m_vect.setY(m_vect.getY() + SHIP_ACELLERATION*sin(m_rotation + PI / 2));
	m_vect.setX(m_vect.getX() + SHIP_ACELLERATION*cos(m_rotation + PI / 2));
}

void Ship::moveLeft()
{
	m_vect.setY(m_vect.getY() - SHIP_ACELLERATION*sin(m_rotation));
	m_vect.setX(m_vect.getX() - SHIP_ACELLERATION*cos(m_rotation));
}

void Ship::moveRight()
{
	m_vect.setY(m_vect.getY() + SHIP_ACELLERATION*sin(m_rotation));
	m_vect.setX(m_vect.getX() + SHIP_ACELLERATION*cos(m_rotation));
}

std::shared_ptr<Projectile> Ship::fireProj()
{
	al_play_sample(firingSound, .5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	return std::make_shared<Projectile>(p1 ,m_rotation);
}

void Ship::updateHook()
{
	//prevent moving faster than the max speed
	if (m_vect.getMagnitude() > MAX_SHIP_SPEED)
	{
		float ratio = MAX_SHIP_SPEED / m_vect.getMagnitude();
		m_vect.setY(m_vect.getY()*ratio);
		m_vect.setX(m_vect.getX()*ratio);
	}

	m_rotation = atan2f(pos.y - m_mousePos.y, pos.x - m_mousePos.x)- PI/2;
	//update ship position
	pos = pos + m_vect;
	//reset transforms
	al_copy_transform(&trans1, &orig1);
	al_copy_transform(&trans2, &orig2);
	al_copy_transform(&trans3, &orig3);
	//rotate the ship to point at the mouse cursor
	al_rotate_transform(&trans1, m_rotation);
	al_rotate_transform(&trans2, m_rotation);
	al_rotate_transform(&trans3, m_rotation);

	transformRotatedShipPointsToWorldCoords();
}

void Ship::render() const
{
	al_draw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, WHITE, 0);
}

void Ship::debugRender() const
{
	al_draw_filled_rectangle(pos.x + 1, pos.y + 1, pos.x - 1, pos.y - 1, RED);
}

bool Ship::destroyCondition()
{
	return false;
}
