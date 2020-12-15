#include "pch.h"
#include "Game.h"
Game::Game(int humanFirst) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			checkerboard[i][j] = 0;
		}
	}
	if (humanFirst == 0) {
		aiPlay();
	}
}
int Game::humanPlay(int x, int y) {
	checkerboard[x][y] = count;
	count++;

	// 如果没结束
	aiPlay();
}
int Game::aiPlay() {
	int x = rand() % SIZE;
	int y = x / SIZE % SIZE;
	checkerboard[x][y] = count++;
}