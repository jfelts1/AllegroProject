#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* testImage = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return EXIT_FAILURE;
	}

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return EXIT_FAILURE;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize allegro image addon!\n");
		return EXIT_FAILURE;
	}

	testImage = al_load_bitmap("Images/test.bmp");
	if (!testImage) {
		fprintf(stderr, "failed to load image\n");
		return EXIT_FAILURE;
	}

	al_draw_bitmap(testImage, 0, 0,0);

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return EXIT_SUCCESS;
}