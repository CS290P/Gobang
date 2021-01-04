#pragma once
#define SIZE 15
#include "Score.h"
class Game
{
public:
	int humanFirst = 1;
	int count = 1;
	int checkBoard[20][20];
	Game(int humanFirst = 1);
	Game();
	int humanPlay(int x, int y);
	int aiPlay();
	int isLive3(int x,int y);
	Score score;
};

