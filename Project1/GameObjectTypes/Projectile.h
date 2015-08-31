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
	Projectile(float x = 0, float y = 0, float rotation = 0,Owner own = Player) :GameObject(x, y, rotation,own)
	{
		Utils::moveForward(m_vect, SPEED, m_rotation);
	}

	Projectile(Point p, float rotation = 0,Owner own = Player) :GameObject(p, rotation,own)
	{
		Utils::moveForward(m_vect, SPEED, m_rotation);
	}

	virtual ~Projectile() { printf("projectile destroyed lifetime was: %i\n",m_lifetime); }

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	// Inherited via GameObject
	virtual void render() const override;
	virtual void debugRender() const override;
private:
	int m_lifetime = 0;
	bool m_hit = false;

	// Inherited via GameObject
	virtual void hitBy(const GameObject * other) override;
};
#endif
