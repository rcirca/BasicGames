#include "Game.h"

void main(int argc, void** argv[])
{
	Game game;
	while(!game.getWindow()->isDone())
	{
		game.handleInput();
		game.update();
		game.render();
		game.restartClock();
	}
}