#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cstdio>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "GameObjectTypes/GameObject.h"
#include "GameObjectTypes/Ship.h"
#include "GameObjectTypes/Projectile.h"
#include "GameObjectTypes/AsteroidFactory.h"
#include "ColorDefines.h"
#include "Point.h"
#include "Utils/GameUtils.h"
#define MS_PER_TICK 16
#define TRACK_TICK_TIMES 0


extern std::vector<std::shared_ptr<GameObject>> GameObjects;
extern std::vector<std::shared_ptr<GameObject>> GameObjectsToAdd;

bool initGameWorld();
void runGame();


#endif
