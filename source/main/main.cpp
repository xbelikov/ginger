#include "main.h"

int main()
{
	std::cout << "Start ginger::Game";
	
	ginger::Game game;

	if(game.start()) {
		game.cycle();
	}

	game.stop();

	return 0;
}