#include "Test.h"

Test::Test(float x, float y, float rotation) : GameObject(x,y,rotation, "Images/test.bmp")
{
}

Test::~Test()
{
}

Test::Test(const Test & orig) : GameObject(orig)
{
}

void Test::updateHook()
{
}

void Test::render() const
{
	al_draw_bitmap(m_sprite, pos.x, pos.y, 0);
}
