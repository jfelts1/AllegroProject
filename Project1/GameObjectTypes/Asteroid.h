#ifndef ASTEROID_H
#define ASTEROID_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "GameObject.h"
#include "../Vector.h"
#define MAX_ASTEROID_SPEED 5
class Asteroid :
	public GameObject
{
public:
	Asteroid(Vector vect, float x = 0, float y = 0, float rotation = 0, const char* filename = "Images/Asteroids/Asteroid1.png") :GameObject(x, y, rotation, filename)
	{
		
	}
	virtual ~Asteroid() {}

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	virtual void render() const override;
	virtual void debugRender() const override;
};
#endif
