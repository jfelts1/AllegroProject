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

void Ship::moveForward()
{
	Utils::moveForward(m_vect, m_shipAcceleration, m_rotation);
}

void Ship::moveBack()
{
	Utils::moveBack(m_vect, m_shipAcceleration, m_rotation);
}

void Ship::moveLeft()
{
	Utils::moveLeft(m_vect, m_shipAcceleration, m_rotation);
}

void Ship::moveRight()
{
	Utils::moveRight(m_vect, m_shipAcceleration, m_rotation);
}

std::shared_ptr<Projectile> Ship::fireProj()
{
	al_play_sample(m_firingSound, .5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	return std::make_shared<Projectile>(m_projMaxLifetime,m_projSpeed, p1 ,m_rotation,Player);
}

void Ship::updateHook()
{
	//prevent moving faster than the max speed
	if (m_vect.getMagnitude() > m_maxShipSpeed)
	{
		float ratio = m_maxShipSpeed / m_vect.getMagnitude();
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

void Ship::initShip(float rotation)
{
	loadShipConsts();
	loadProjConsts();
	p1.x = pos.x;
	p1.y = pos.y - (m_shipHeight / 2);

	p2.x = pos.x - (m_shipWidth / 2);
	p2.y = pos.y + (m_shipHeight / 2);

	p3.x = pos.x + (m_shipWidth / 2);
	p3.y = pos.y + (m_shipHeight / 2);

	initTransforms(orig1, orig2, orig3);
	initTransforms(trans1, trans2, trans3);

	al_rotate_transform(&trans1, rotation);
	al_rotate_transform(&trans2, rotation);
	al_rotate_transform(&trans3, rotation);

	transformRotatedShipPointsToWorldCoords();

	m_firingSound = al_load_sample("Sounds/Laser_Shoot2.wav");
	m_deathSound = al_load_sample("Sounds/Explosion.wav");

	m_collisionRadius = (m_shipHeight + m_shipWidth) / 2;
}

void Ship::loadShipConsts()
{
	std::string shipInfo = Utils::getGameConstsTagInfo(Utils::Ship);
	std::cout << shipInfo << std::endl;
	m_shipHeight = Utils::getFloatFromStringWPrefix(shipInfo, "shipHeight=");
	m_shipWidth = Utils::getFloatFromStringWPrefix(shipInfo, "shipWidth=");
	m_maxShipSpeed = Utils::getFloatFromStringWPrefix(shipInfo, "maxShipSpeed=");
	m_shipAcceleration = Utils::getFloatFromStringWPrefix(shipInfo, "shipAcelleration=");
}

void Ship::loadProjConsts()
{
	std::string projInfo = Utils::getGameConstsTagInfo(Utils::Projectile);
	std::cout << projInfo << std::endl;
	m_projMaxLifetime = Utils::getIntFromStringWPreFix(projInfo, "maxLifetime=");
	m_projSpeed = Utils::getFloatFromStringWPrefix(projInfo, "speed=");
}

void Ship::hitBy(const GameObject * other)
{
	if (other->getOwner() == World)
	{
		m_collided = true;
	}
}

bool Ship::destroyCondition()
{
	if (m_collided == true)
	{
		al_play_sample(m_deathSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		return true;
	}
	return false;
}
