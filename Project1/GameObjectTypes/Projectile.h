#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include "GameObject.h"
#include "../Point.h"
#include "../ColorDefines.h"
#define MAX_LIFETIME 20
#define SPEED 50
class Projectile :
	public GameObject
{
public:
	Projectile(float x = 0, float y = 0, float rotation = 0) :GameObject(x, y, rotation)
	{
		m_vect.setY(m_vect.getY() - SPEED*sin(m_rotation + PI / 2));
		m_vect.setX(m_vect.getX() - SPEED*cos(m_rotation + PI / 2));
	}

	Projectile(Point p, float rotation = 0) :GameObject(p, rotation)
	{
		m_vect.setY(m_vect.getY() - SPEED*sin(m_rotation + PI / 2));
		m_vect.setX(m_vect.getX() - SPEED*cos(m_rotation + PI / 2));
	}

	virtual ~Projectile() { /*printf("projectile destroyed lifetime was: %i\n",m_lifetime);*/ }

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	// Inherited via GameObject
	virtual void render() const override;
	virtual void debugRender() const override;
private:
	int m_lifetime = 0;

	
};
#endif
