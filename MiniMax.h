#pragma once
#include "ChosePlace.h"

struct Chess
{
	int x, y;
	int prior;
};

class MiniMax:public ChosePlace {
	int score;
	Chess ai_next_move;
	MiniMax* son1;
	MiniMax* son2;
	MiniMax* son3;
	MiniMax* son4;
	MiniMax* son5;
	MiniMax* son6;
	int MiniMax::GetPossibleChoice(Chess* possible_choice, int** Board) {};
	int MiniMaxST(int id,int** Board,int depth,int alpha,int beta) {};
	
};