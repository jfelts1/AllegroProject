#ifndef UI_H
#define UI_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "Utils/ScreenUtils.h"
#include "ColorDefines.h"

#pragma once
class Ui
{
public:
	Ui();
	virtual ~Ui();

	void render();

private:
	ALLEGRO_FONT* arial;
	std::string m_asteroidDestroyedString = "Asteroids destroyed: ";
};
#endif
