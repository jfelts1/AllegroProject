#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include "GameObject.h"
#include "../Point.h"
#include "../ColorDefines.h"

class Projectile :
	public GameObject
{
public:
	Projectile(int maxLifetime, float speed,float x = 0, float y = 0, float rotation = 0,Owner own = Player) :GameObject(x, y, rotation,own)
	{
		m_maxLifetime = maxLifetime;
		m_speed = speed;
		Utils::moveForward(m_vect, m_speed, m_rotation);
	}

	Projectile(int maxLifetime, float speed, Point p, float rotation = 0,Owner own = Player) :GameObject(p, rotation,own)
	{
		m_maxLifetime = maxLifetime;
		m_speed = speed;
		Utils::moveForward(m_vect, m_speed, m_rotation);
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
	float m_speed;
	int m_maxLifetime;

	// Inherited via GameObject
	virtual void hitBy(const GameObject * other) override;
};
#endif
