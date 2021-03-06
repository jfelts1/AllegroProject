#ifndef SPRITEUTILS_H
#define SPRITEUTILS_H
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>

namespace Utils
{
	extern ALLEGRO_BITMAP* getSprite(const char* filename);
	void cleanSpriteMap();
}

#endif
