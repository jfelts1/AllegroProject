#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "GameObjectTypes/GameObject.h"
#include "GameObjectTypes/Test.h"
#include <memory>
#include <vector>

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY* display = nullptr;
	//std::shared_ptr<ALLEGRO_BITMAP*> testImage;
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

	/*testImage = std::make_shared<ALLEGRO_BITMAP*>(al_load_bitmap("Images/test.bmp"));
	if (testImage == nullptr) 
	{
		fprintf(stderr, "failed to load image\n");
		return EXIT_FAILURE;
	}*/

	events = al_create_event_queue();
	if (events == nullptr) 
	{
		fprintf(stderr, "failed to create event queue\n");
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
		while(!quit)
		{
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
						test.push_back(std::make_shared<Test>((float)mouseEvent.x, (float)mouseEvent.y,0));
					}
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
		}
	}
	else 
	{
		fprintf(stderr, "no mouse found or keyboard!\n");
		return EXIT_FAILURE;
	}

	for (auto spritesToRend : test)
	{
		spritesToRend->render();
		al_flip_display();
	}

	al_flip_display();
	al_rest(5);
	al_destroy_display(display);

	al_destroy_event_queue(events);

	return EXIT_SUCCESS;
}