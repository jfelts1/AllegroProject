#ifndef ASTEROID_H
#define ASTEROID_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//#include <cstdio>
#include "GameObject.h"
#include "../Vector.h"

class Asteroid :
	public GameObject
{
public:
	Asteroid(Vector vect, float x = 0, float y = 0, float rotation = 0, const char* filename = "Images/Asteroids/Asteroid1.png") :GameObject(x, y, rotation, filename)
	{
		m_vect = vect;
	}
	virtual ~Asteroid() {}

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	virtual void render() const override;
	virtual void debugRender() const override;
};
#endif
