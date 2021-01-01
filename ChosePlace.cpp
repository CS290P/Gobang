#include "pch.h"
#include "ChosePlace.h"
int Board[15][15];

int neibor(int x, int y) {
	for (int i = x - 2; i < x + 2; i++) {
		for (int j = y - 2; j < y + 2; j++) {
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