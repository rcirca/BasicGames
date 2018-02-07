#include "Game.h"
#include "GameMushroom.h"

void main(int argc, void** argv)
{
	Game game;
	while(!game.getWindow()->isDone())
	{
		game.update();
		game.render();
		game.restartClock();
	}
}
