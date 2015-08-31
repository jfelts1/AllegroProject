#ifndef ASTEROID_H
#define ASTEROID_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//#include <cstdio>
#include "GameObject.h"
#include "../Vector.h"

extern int asteroidCount;

class Asteroid :
	public GameObject
{
public:
	Asteroid(Vector vect, float x = 0, float y = 0, float rotation = 0,float rotationRate = 0, const char* filename = "Images/Asteroids/Asteroid1.png") :GameObject(x, y, rotation,World, filename)
	{
		m_vect = vect;
		asteroidCount++;
		m_rotationRate = rotationRate;
		pos.x = pos.x + (m_spriteWidth / 2);
		pos.y = pos.y + (m_spriteHeight / 2);
		//std::cout << asteroidCount << std::endl;
	}
	virtual ~Asteroid() {}

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	virtual void render() const override;
	virtual void debugRender() const override;
private:
	float m_rotationRate = 0;

	// Inherited via GameObject
	virtual void hitBy(const GameObject * other) override;
};
#endif
