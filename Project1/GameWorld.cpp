#include "GameWorld.h"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::vector;
using std::shared_ptr;
using std::make_shared;

vector<shared_ptr<GameObject>> GameObjects;
vector<shared_ptr<GameObject>> GameObjectsToAdd;
shared_ptr<Ship> player;

ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* events = nullptr;

ALLEGRO_EVENT_SOURCE* mouseEventSource = nullptr;
ALLEGRO_EVENT_SOURCE* keyboardEventSource = nullptr;


bool initGameWorld()
{
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	display = al_create_display(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	if (display == nullptr)
	{
		fprintf(stderr, "failed to create display!\n");
		return false;
	}

	if (!al_init_image_addon())
	{
		fprintf(stderr, "failed to initialize allegro image addon!\n");
		return false;
	}

	events = al_create_event_queue();
	if (events == nullptr)
	{
		fprintf(stderr, "failed to create event queue\n");
		return false;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize allegro primitives addon!\n");
		return false;
	}

	if (!al_install_audio())
	{
		fprintf(stderr, "failed to install audio system\n");
		return false;
	}

	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to init audio codec system\n");
		return false;
	}

	if (!al_reserve_samples(5))
	{
		fprintf(stderr, "failed to reserve audio samples\n");
		return false;
	}

	if (!al_install_mouse())
	{
		fprintf(stderr, "no mouse found!\n");
		return false;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "no keyboard found!\n");
		return false;
	}

	return true;
}

void runGame()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	mouseEventSource = al_get_mouse_event_source();
	keyboardEventSource = al_get_keyboard_event_source();
	al_register_event_source(events, mouseEventSource);
	al_register_event_source(events, keyboardEventSource);
	GameObjects.push_back(make_shared<Ship>(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2));
	shared_ptr<GameObject> tmp = GameObjects[0];
	player = std::static_pointer_cast<Ship>(tmp);
	GameObjects.push_back(make_shared<AsteroidFactory>());
	bool quit = false;
	//main game loop
	while (!quit)
	{
		auto startTime = high_resolution_clock::now();

#if TRACK_TICK_TIMES == 1
		auto startInputUpdateTime = high_resolution_clock::now();
#endif
		//add new GameObjects at the start of the gametick
		for (auto obj : GameObjectsToAdd)
		{
			GameObjects.push_back(obj);
		}
		GameObjectsToAdd.clear();
		quit = Utils::getUserInput(events,player);
		Utils::updateGameState();
#if TRACK_TICK_TIMES == 1
		auto endInputUpdateTime = high_resolution_clock::now();
		auto startRenderTime = high_resolution_clock::now();
#endif
		Utils::renderGameState();
#if TRACK_TICK_TIMES == 1
		auto endRenderTime = high_resolution_clock::now();
#endif

		auto endTime = high_resolution_clock::now();
		auto gameTickTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
#if TRACK_TICK_TIMES == 1
		auto inputUpdateTime = duration_cast<std::chrono::milliseconds>(endInputUpdateTime - startInputUpdateTime).count();
		auto renderTime = duration_cast<std::chrono::milliseconds>(endRenderTime - startRenderTime).count();
		printf("Input and Update Time: %lld  Render Time: %lld  ", inputUpdateTime, renderTime);
		printf("Time elapsed: %lld  Waiting for: %lld\n", gameTickTime, MS_PER_TICK - gameTickTime);
#endif
		std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_TICK - gameTickTime));
	}

	al_flip_display();
	al_rest(1);
	al_destroy_display(display);

	al_destroy_event_queue(events);
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
}
