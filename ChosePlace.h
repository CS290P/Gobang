#pragma once
class ChosePlace {
public:
	int possible_choice[100][2];
	int size = 0;
	int ChosePlace::neibor_R1(int x, int y,int** Board) {};
	int ChosePlace::neibor_R2(int x, int y, int** Board) {};
	void ChosePlace::PutChess(int x, int y, int id, int** Board) {};
	void ChosePlace::RollBackChess(int x, int y, int** Board) {};
	void ChosePlace::GetPossibleChoice(int** Board) {};
};