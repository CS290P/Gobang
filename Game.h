#pragma once
#define SIZE 15
class Game
{
public:
	int humanFirst = 1;
	int count = 1;
	int checkerboard[15][15];
	Game(int humanFirst = 1);
	Game();
	int humanPlay(int x, int y);
	int aiPlay();
};

