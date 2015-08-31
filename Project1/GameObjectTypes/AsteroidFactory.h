#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <random>
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../Utils/SpriteUtils.h"
#include "../Utils/GameUtils.h"
#include "../Utils/FileUtils.h"
#include "../Vector.h"
#include "GameObject.h"
#include "Asteroid.h"

extern int asteroidCount;

class AsteroidFactory :
	public GameObject
{
public:
	AsteroidFactory() 
	{
		loadAsteroidSpriteFiles();
		loadAsteroidValues();
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

	float m_asteroidSpawnChance = 0.05f;
	int m_maxAsteroids = 10;
	float m_maxAsteroidSpeed = 5.0f;
	float m_maxAsteroidRoationRate = 0.15707963267948966192313216916398f;

	void loadAsteroidSpriteFiles();
	void loadAsteroidValues();

	// Inherited via GameObject
	virtual void hitBy(const GameObject * other) override;
};
#endif
