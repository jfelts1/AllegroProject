#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_BITMAP* testImage = nullptr;
	ALLEGRO_EVENT_QUEUE* events = nullptr;
	ALLEGRO_MOUSE_EVENT mouseEvent;
	ALLEGRO_EVENT_SOURCE* mouseEventSource = nullptr;
	ALLEGRO_EVENT mouseClick;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return EXIT_FAILURE;
	}

	display = al_create_display(640, 480);
	if (display == nullptr) {
		fprintf(stderr, "failed to create display!\n");
		return EXIT_FAILURE;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize allegro image addon!\n");
		return EXIT_FAILURE;
	}

	testImage = al_load_bitmap("Images/test.bmp");
	if (testImage == nullptr) {
		fprintf(stderr, "failed to load image\n");
		return EXIT_FAILURE;
	}

	events = al_create_event_queue();
	if (events == nullptr) {
		fprintf(stderr, "failed to create event queue\n");
		return EXIT_FAILURE;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	if (al_install_mouse()) {
		mouseEventSource = al_get_mouse_event_source();
		al_register_event_source(events, mouseEventSource);
		while (true)
		{
			while (!al_is_event_queue_empty(events))
			{	
				al_get_next_event(events, &mouseClick);
				ALLEGRO_EVENT_TYPE ty = mouseClick.type;
				if (ty == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					mouseEvent = mouseClick.mouse;
					if (mouseEvent.button & 1)
					{
						printf("mouse click at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
						al_draw_bitmap(testImage, mouseEvent.x, mouseEvent.y, 0);
						al_flip_display();
					}
				}
			}
		}
		
		
	}
	else {
		fprintf(stderr, "no mouse found!\n");
		return EXIT_FAILURE;
	}

	al_rest(5);
	al_destroy_display(display);

	al_destroy_event_queue(events);

	return EXIT_SUCCESS;
}