#include "ScreenUtils.h"
namespace Utils
{
	void screenWrap(Point& p)
	{
		p.x = fmod(p.x ,SCREEN_SIZE_X);
		if (p.x < 0)
		{
			p.x = SCREEN_SIZE_X;
		}
		p.y = fmod(p.y, SCREEN_SIZE_Y);
		if (p.y < 0)
		{
			p.y = SCREEN_SIZE_Y;
		}
	}
}

