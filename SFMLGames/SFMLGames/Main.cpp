#include "Game.h"
#include "GameMushroom.h"
#include "StateGameTest.h"
void main(int argc, void** argv)
{
	StateGameTest game;
	while(!game.getWindow()->isDone())
	{
		game.update();
		game.render();
		game.lateUpdate();
	}
}
