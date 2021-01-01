#include "pch.h"
#include "ChosePlace.h"
#include "Score.h"
//int Board[15][15];

int ChosePlace::neibor_R1(int x, int y, int** Board) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i == x && j == y)
				continue;
			if (i >= 0 && i <= 14 && j >= 0 && j <= 14) {
				if (Board[i][j] != 0)
					return 1;
			}
		}
	}
	return 0;
}

int ChosePlace::neibor_R2(int x, int y,int** Board) {
	for (int i = x - 2; i <= x + 2; i++) {
		for (int j = y - 2; j <= y + 2; j++) {
			if (i == x && j == y)
				continue;
			if (i >= 0 && i <= 14 && j >= 0 && j <= 14) {
				if (Board[i][j] != 0)
					return 1;
			}
		}
	}
	return 0;
}

void ChosePlace::PutChess(int x, int y, int id,int** Board) {
	if (Board[x][y] != 0)
		return;
	else if (Board[x][y] == 0)
		Board[x][y] = id;
	return;
}

void ChosePlace::RollBackChess(int x, int y, int** Board) {
	Board[x][y] = 0;
	return;
}


