#include "AsteroidFactory.h"

void AsteroidFactory::updateHook()
{
	float r = (float)m_rand();
	if (ASTEROID_SPAWN_CHANCE > (r / UINT_MAX))
	{
		std::string randFilename = m_spriteFiles[(m_rand() % m_spriteFiles.size())];
		Vector v;
		v.setX(m_rand() % MAX_ASTEROID_SPEED);
		v.setY(m_rand() % MAX_ASTEROID_SPEED);
		//printf("x: %f y:%f\n", v.getX(), v.getY());
		std::shared_ptr<GameObject> newAsteroid = std::make_shared<Asteroid>(v,m_rand()%SCREEN_SIZE_X, m_rand()%SCREEN_SIZE_Y,fmod(m_rand(),PI), randFilename.c_str());
		Utils::addGameObject(newAsteroid);
		//puts(randFilename.c_str());
	}
}

bool AsteroidFactory::destroyCondition()
{
	return false;
}

void AsteroidFactory::render() const
{
}

void AsteroidFactory::debugRender() const
{
}

void AsteroidFactory::loadAsteroidSpriteFiles()
{
	ALLEGRO_FS_ENTRY* f = al_create_fs_entry("Images/Asteroids");
	al_open_directory(f);
	ALLEGRO_FS_ENTRY* file = al_read_directory(f);
	while (file != nullptr)
	{
		const char* tmp = al_get_fs_entry_name(file);
		m_spriteFiles.push_back(tmp);
		al_destroy_fs_entry(file);
		file = al_read_directory(f);
	}
	al_close_directory(f);
	al_destroy_fs_entry(f);
}
