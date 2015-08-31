#include "AsteroidFactory.h"

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

void AsteroidFactory::updateHook()
{
	if (asteroidCount < m_maxAsteroids)
	{
		float r = (float)m_rand();
		if (m_asteroidSpawnChance > (r / UINT_MAX))
		{
			string randFilename = m_spriteFiles[(m_rand() % m_spriteFiles.size())];
			Vector v;
			v.setX(fmod(m_rand(),m_maxAsteroidSpeed));
			v.setY(fmod(m_rand(),m_maxAsteroidSpeed));
			//printf("x: %f y:%f\n", v.getX(), v.getY());
			float xPos = m_rand() % SCREEN_SIZE_X;
			float yPos = m_rand() % SCREEN_SIZE_Y;
			float rotation = fmod(m_rand(), PI);
			float rotationRate = fmod(m_rand(), m_maxAsteroidRoationRate);
			std::shared_ptr<GameObject> newAsteroid = std::make_shared<Asteroid>(v ,xPos ,yPos ,rotation,rotationRate, randFilename.c_str());
			Utils::addGameObject(newAsteroid);
			//puts(randFilename.c_str());
		}
	}
}

bool AsteroidFactory::destroyCondition()
{
	return false;
}

//renders nothing
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
		ALLEGRO_PATH* asteroidAbsPath = al_create_path(tmp);
		string tmp2 = al_get_path_filename(asteroidAbsPath);
		string asteroidRelPath = "Images/Asteroids/" + tmp2;
		//std::cout << asteroidRelPath << std::endl;
		m_spriteFiles.push_back(asteroidRelPath);
		//loads the sprite into memory
		Utils::getSprite(asteroidRelPath.c_str());
		al_destroy_path(asteroidAbsPath);
		al_destroy_fs_entry(file);
		file = al_read_directory(f);
	}
	al_close_directory(f);
	al_destroy_fs_entry(f);
}

void AsteroidFactory::loadAsteroidValues()
{
	string asteroidInfo = Utils::getGameConstsTagInfo(Utils::Asteroids);
	cout << asteroidInfo << endl;
	m_asteroidSpawnChance = Utils::getFloatFromStringWPrefix(asteroidInfo, "asteroidSpawnChance=");
	m_maxAsteroids = Utils::getIntFromStringWPreFix(asteroidInfo, "maxAsteroids=");
	m_maxAsteroidSpeed = Utils::getFloatFromStringWPrefix(asteroidInfo, "maxAsteroidSpeed=");
	m_maxAsteroidRoationRate = Utils::getFloatFromStringWPrefix(asteroidInfo, "maxRotationRate=");
}


#if _WIN32
#pragma warning(disable: 4100)
#endif
void AsteroidFactory::hitBy(const GameObject * other)
{
}
#if _WIN32
#pragma warning(default: 4100)
#endif
