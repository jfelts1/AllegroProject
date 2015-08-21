#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "GameObjectTypes/GameObject.h"
#include "GameObjectTypes/Test.h"
#include "GameObjectTypes/Ship.h"
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#define MS_PER_TICK 16

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_EVENT_QUEUE* events = nullptr;
	ALLEGRO_MOUSE_EVENT mouseEvent;
	ALLEGRO_EVENT_SOURCE* mouseEventSource = nullptr;
	ALLEGRO_EVENT_SOURCE* keyboardEventSource = nullptr;
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_EVENT keyboardEvent;

	if (!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return EXIT_FAILURE;
	}

	display = al_create_display(640, 480);
	if (display == nullptr) 
	{
		fprintf(stderr, "failed to create display!\n");
		return EXIT_FAILURE;
	}

	if (!al_init_image_addon()) 
	{
		fprintf(stderr, "failed to initialize allegro image addon!\n");
		return EXIT_FAILURE;
	}

	events = al_create_event_queue();
	if (events == nullptr) 
	{
		fprintf(stderr, "failed to create event queue\n");
		return EXIT_FAILURE;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize allegro primitives addon!\n");
		return EXIT_FAILURE;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

	std::vector<std::shared_ptr<GameObject>> test;

	if (al_install_mouse() && al_install_keyboard()) 
	{
		mouseEventSource = al_get_mouse_event_source();
		keyboardEventSource = al_get_keyboard_event_source();
		al_register_event_source(events, mouseEventSource);
		al_register_event_source(events, keyboardEventSource);
		bool quit = false;
		//main game loop

		while(!quit)
		{
			auto startTime = high_resolution_clock::now();
			while (!al_is_event_queue_empty(events))
			{	
				al_get_next_event(events, &event);
				ALLEGRO_EVENT_TYPE ty = event.type;
				if (ty == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					mouseEvent = event.mouse;
					if (mouseEvent.button & 1)
					{
						printf("mouse click at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
					}
				}
				if (ty == ALLEGRO_EVENT_MOUSE_AXES)
				{
					mouseEvent = event.mouse;
					printf("mouse at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
				}
				if (ty == ALLEGRO_EVENT_KEY_DOWN)
				{
					keyboardEvent = event.keyboard;
					if (keyboardEvent.keycode == ALLEGRO_KEY_Q)
					{
						quit = true;
					}
				}
			}
			auto endTime = high_resolution_clock::now();
			auto gameTickTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
			std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_TICK - gameTickTime));
		}
	}
	else 
	{
		fprintf(stderr, "no mouse or keyboard found!\n");
		return EXIT_FAILURE;
	}

	for (auto spritesToRend : test)
	{
		spritesToRend->update();
		spritesToRend->render();
		al_flip_display();
	}

	al_flip_display();
	al_rest(5);
	al_destroy_display(display);

	al_destroy_event_queue(events);

	return EXIT_SUCCESS;
}
