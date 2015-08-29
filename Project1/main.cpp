#include <cstdio>
#include "GameWorld.h"

int main(int argc, char **argv)
{
	if (!initGameWorld())
	{
		return EXIT_FAILURE;
	}

	runGame();
	shutdownGameWorld();

	return EXIT_SUCCESS;
}
