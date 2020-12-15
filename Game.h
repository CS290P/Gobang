#pragma once
#define SIZE 15
class Game
{
private:
	int count = 1;
	int size;
	int checkerboard[15][15];
public:
	Game(int humanFirst = 1);
	int humanPlay(int x, int y);
	int aiPlay();
};

