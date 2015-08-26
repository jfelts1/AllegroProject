#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <random>
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include "../Utils/SpriteUtils.h"
#include "../Utils/GameUtils.h"
#include "../Vector.h"
#include "GameObject.h"
#include "Asteroid.h"
#define ASTEROID_SPAWN_CHANCE .05



class AsteroidFactory :
	public GameObject
{
public:
	AsteroidFactory() 
	{
		loadAsteroidSpriteFiles();
	}
	virtual ~AsteroidFactory() {}

	virtual void updateHook() override;
	// Inherited via GameObject
	virtual bool destroyCondition() override;
	virtual void render() const override;
	virtual void debugRender() const override;
private:
	std::mt19937 m_rand;
	std::vector<std::string> m_spriteFiles;

	void loadAsteroidSpriteFiles();
};
#endif
