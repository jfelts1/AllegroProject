#include "GameWorld.h"

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::vector;
using std::shared_ptr;
using std::make_shared;

vector<shared_ptr<GameObject>> GameObjects;
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
	bool quit = false;
	//main game loop
	while (!quit)
	{
		auto startTime = high_resolution_clock::now();

		auto startInputUpdateTime = high_resolution_clock::now();
		quit = Utils::getUserInput(events,player);
		Utils::updateGameState();
		auto endInputUpdateTime = high_resolution_clock::now();
		auto startRenderTime = high_resolution_clock::now();
		Utils::renderGameState();
		auto endRenderTime = high_resolution_clock::now();

		auto endTime = high_resolution_clock::now();
		auto gameTickTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
		auto inputUpdateTime = duration_cast<std::chrono::milliseconds>(endInputUpdateTime - startInputUpdateTime).count();
		auto renderTime = duration_cast<std::chrono::milliseconds>(endRenderTime - startRenderTime).count();
		printf("Input and Update Time: %lldms		Render Time: %lldms\n", inputUpdateTime, renderTime);
		//printf("Time elapsed: %lldms   Waiting for: %lldms\n", gameTickTime, MS_PER_TICK - gameTickTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_TICK - gameTickTime));
	}

	al_flip_display();
	al_rest(1);
	al_destroy_display(display);

	al_destroy_event_queue(events);
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
}

/*bool getUserInput()
{
	shared_ptr<GameObject> tmp = GameObjects[0];
	shared_ptr<Ship> player = std::static_pointer_cast<Ship>(tmp);
	static bool forMovementKeyHeld;
	static bool backMovementKeyHeld;
	static bool leftMovementKeyHeld;
	static bool rightMovementKeyHeld;

	while (!al_is_event_queue_empty(events))
	{
		al_get_next_event(events, &event);
		ALLEGRO_EVENT_TYPE ty = event.type;
		if (ty == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouseEvent = event.mouse;
			if (mouseEvent.button & 1)
			{
				//printf("mouse click at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
				shared_ptr<Projectile> proj = player->fireProj();
				GameObjects.push_back(proj);
			}
		}
		//mouse was moved
		if (ty == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouseEvent = event.mouse;
			mouseCurPos.getCurMousePos(mouseEvent);
			player->setRotationTarget(mouseCurPos);
			//printf("mouse at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
		}
		//key was pressed
		if (ty == ALLEGRO_EVENT_KEY_DOWN)
		{
			keyboardEvent = event.keyboard;
			if (keyboardEvent.keycode == QUIT)
			{
				return true;
			}
			else if (keyboardEvent.keycode == MOVE_FORWARD)
			{
				forMovementKeyHeld = true;
			}
			else if (keyboardEvent.keycode == MOVE_BACK)
			{
				backMovementKeyHeld = true;
			}
			else if (keyboardEvent.keycode == MOVE_LEFT)
			{
				leftMovementKeyHeld = true;
			}
			else if (keyboardEvent.keycode == MOVE_RIGHT)
			{
				rightMovementKeyHeld = true;
			}
			else if (keyboardEvent.keycode == DEBUG_RENDERING_TOGGLE)
			{
				enableDebugRendering = !enableDebugRendering;
			}
		}

		if (forMovementKeyHeld)
		{
			player->moveFor();
		}
		if (backMovementKeyHeld)
		{
			player->moveBack();
		}
		if (leftMovementKeyHeld)
		{
			player->moveLeft();
		}
		if (rightMovementKeyHeld)
		{
			player->moveRight();
		}

		//key was released
		if (ty == ALLEGRO_EVENT_KEY_UP)
		{
			keyboardEvent = event.keyboard;
			if (keyboardEvent.keycode == MOVE_FORWARD)
			{
				forMovementKeyHeld = false;
			}
			else if (keyboardEvent.keycode == MOVE_BACK)
			{
				backMovementKeyHeld = false;
			}
			else if (keyboardEvent.keycode == MOVE_LEFT)
			{
				leftMovementKeyHeld = false;
			}
			else if (keyboardEvent.keycode == MOVE_RIGHT)
			{
				rightMovementKeyHeld = false;
			}
		}
	}
	return false;
}*/

/*void updateGameState()
{
	vector<int> objectsToRemove;
	int i = 0;
	//while updating check objects if they should be destroyed
	for (auto GameObjsToUpdate : GameObjects)
	{
		if (GameObjsToUpdate->destroyCondition())
		{
			objectsToRemove.push_back(i);
		}
		else
		{
			GameObjsToUpdate->update();
		}
		i++;
	}

	for (auto rem : objectsToRemove)
	{
		GameObjects.erase(GameObjects.begin() + rem);
	}
	objectsToRemove.clear();
}

void renderGameState()
{
	//clear existing frame
	al_clear_to_color(BLACK);
	//render new frame
	for (auto GameObjsToRender : GameObjects)
	{
		GameObjsToRender->render();
		if (enableDebugRendering)
		{
			GameObjsToRender->debugRender();
		}
	}
	al_flip_display();
}*/
