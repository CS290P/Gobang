#include "pch.h"
#include "Game.h"
Game::Game(int humanFirst) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			checkBoard[i][j] = 0;
		}
	}
	this->humanFirst = humanFirst;
	checkBoard[7][7] = 1;
	Score s((int**)checkBoard);
	score = s;
}
int Game::humanPlay(int x, int y) {
	if (checkBoard[x][y] != 0) {
		return 0;
	}
	checkBoard[x][y] = -1;
	count++;
	return 1;
}
int Game::aiPlay() {
	int** Board;
	int row = 15, column = 15;
	Board = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
	{
		Board[i] = (int*)malloc(sizeof(int) * (column));
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			Board[i][j] = checkBoard[i][j];
		}
	}

	int x_ai, y_ai;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {

		}
	}

	int x = Board[0][0];
	if (score.numof_P4(Board, -1) == 1) {  //�û��г��ĵ�ʱ��ض� ���ȼ����
		Chess next = score.SleepEnemyP4((int**)Board);
		x_ai = next.x;
		y_ai = next.y;
		score.PutChess(x_ai, y_ai, 1, (int**)Board);
	}
	else if (score.numof_P4(Board, 1) == 1) {   //AI�л��������ʱ���ɱ �з����ǳ������Լ��л������� ��ô�����������Ϸ
		Chess next = score.AIGotoC5(Board);
		x_ai = next.x;
		y_ai = next.y;
		score.PutChess(x_ai, y_ai, 1, Board);
	}
	else if (score.numof_A4(Board, 1) == 1) {   //AI�л��������ʱ���ɱ �з����ǳ������Լ��л������� ��ô�����������Ϸ
		Chess next = score.AIGotoC5(Board);
		x_ai = next.x;
		y_ai = next.y;
		score.PutChess(x_ai, y_ai, 1, Board);
	}
	else if (score.numof_A3(Board, 1) == 1) {   //AI�л����������Ҷ����޳��� ��ôAI�ͽ������
		Chess next = score.AIGotoA4(Board);
		x_ai = next.x;
		y_ai = next.y;
		score.PutChess(x_ai, y_ai, 1, Board);
	}
	else if (score.numof_A3(Board, -1) == 1) {   //�û��л�����ʱ��ض�
		Chess next = score.SleepEnemyA3(Board);
		x_ai = next.x;
		y_ai = next.y;
		score.PutChess(x_ai, y_ai, 1, Board);
	}
	else {
		score.MiniMaxST(1, Board, 0, -300000, 300000);
		x_ai = score.ai_next_move.x;
		y_ai = score.ai_next_move.y;
		score.PutChess(x_ai, y_ai, 1, Board);
	}


	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			checkBoard[i][j]= Board[i][j];
		}
	}
	if (score.numof_C5(Board, 1) > 0) {
		return 1;
	}
	if (score.numof_C5(Board, -1) > 0) {
		return -1;
	}
	return 0;
}


Game::Game() {}