#include "pch.h"
#include "Game.h"
Game::Game(int humanFirst) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			checkerboard[i][j] = 0;
		}
	}
	this->humanFirst = humanFirst;
	if (humanFirst == 0) {
		aiPlay();
	}
}
int Game::humanPlay(int x, int y) {
	checkerboard[x][y] = count;
	count++;

	return 0;
}
int Game::aiPlay() {
	srand(time(0));
	int x = rand() % SIZE;
	int y = rand() % SIZE;
	if (checkerboard[x][y] != 0) {
		x = rand() % SIZE;
		y = rand() % SIZE;
	}
	checkerboard[x][y] = -count;
	count++;

	return 0;
}
Game::Game() {}