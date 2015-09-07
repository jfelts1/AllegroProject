#include "Ui.h"

extern int asteroidsDestroyed;

Ui::Ui()
{
	arial = al_load_ttf_font("Fonts/arial.ttf",24,0);
}


Ui::~Ui()
{
	al_destroy_font(arial);
}

void Ui::render()
{
	std::string temp = m_asteroidDestroyedString + std::to_string(asteroidsDestroyed);
	al_draw_text(arial, WHITE, 0, 0,0, temp.c_str());
}
