#include "PhysicsUtils.h"

void Utils::moveForward(Vector& vect, float acelleration, float rotation)
{
	float rot = rotation + (float)PI / 2.0f;
	vect.setY(vect.getY() - acelleration*sin(rot));
	vect.setX(vect.getX() - acelleration*cos(rot));
}

void Utils::moveBack(Vector & vect, float acelleration, float rotation)
{
	float rot = rotation + (float)PI / 2.0f;
	vect.setY(vect.getY() + acelleration*sin(rot));
	vect.setX(vect.getX() + acelleration*cos(rot));
}

void Utils::moveLeft(Vector & vect, float acelleration, float rotation)
{
	vect.setY(vect.getY() - acelleration*sin(rotation));
	vect.setX(vect.getX() - acelleration*cos(rotation));
}

void Utils::moveRight(Vector & vect, float acelleration, float rotation)
{
	vect.setY(vect.getY() + acelleration*sin(rotation));
	vect.setX(vect.getX() + acelleration*cos(rotation));
}
