#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H
#pragma once
#include "../Vector.h"
#define PI 3.1415926535897932384626433832795
namespace Utils
{
	void moveForward(Vector& vect, float acelleration, float rotation);
	void moveBack(Vector& vect, float acelleration, float rotation);
	void moveLeft(Vector& vect, float acelleration, float rotation);
	void moveRight(Vector& vect, float acelleration, float rotation);

}
#endif
