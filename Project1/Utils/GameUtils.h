#ifndef GAMEUTILS_H
#define GAMEUTILS_H
#pragma once
#include <allegro5/allegro.h>
#include <vector>
#include <memory>
#include "../GameObjectTypes/GameObject.h"
#include "../GameObjectTypes/Ship.h"
#include "../GameObjectTypes/Projectile.h"
#include "../Point.h"

extern std::vector<std::shared_ptr<GameObject>> GameObjects;
extern std::vector<std::shared_ptr<GameObject>> GameObjectsToAdd;

namespace Utils
{
	bool getUserInput(ALLEGRO_EVENT_QUEUE* events, std::shared_ptr<::Ship> player);
	void updateGameState();
	void renderGameState();
	void addGameObject(std::shared_ptr<GameObject> obj);
}
#endif
