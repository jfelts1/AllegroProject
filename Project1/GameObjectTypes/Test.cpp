#include "Test.h"

Test::Test(float x, float y, float rotation) : GameObject("Images/test.bmp",x,y,rotation)
{
}

Test::~Test()
{
}

void Test::update() const
{
}

void Test::render() const
{
	al_draw_bitmap(m_sprite, m_x, m_y, 0);
}
