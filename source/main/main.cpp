#include "main.h"

int main()
{
	setlocale(LC_ALL, "");
	
	ginger::Game game;

	if(game.start()) {
		game.cycle();
	}

	game.stop();

	return 0;
}