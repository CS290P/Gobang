#pragma once
class Score
{
public:
	int** map;
	int size;
	Score(int** p, int size) {};
	int getScore(int x,int y,int id);
};

