#include "SpriteUtils.h"

namespace Utils
{
	std::map<const char*, ALLEGRO_BITMAP*> spriteMap;

	ALLEGRO_BITMAP * getSprite(const char * filename)
	{
		auto search = spriteMap.find(filename);
		if (search != spriteMap.end())
		{
			return search->second;
		}
		else
		{
			spriteMap[filename] = al_load_bitmap(filename);
			return spriteMap[filename];
		}
	}
}
