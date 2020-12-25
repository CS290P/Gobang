#pragma once
#define C5score  135000   // 连五
#define A4score  25000   // 活四
#define P4score  5201   // 冲四
#define A3score  4991   // 活三
#define S3score  410  // 眠三
#define A2score  450  // 活二
#define S2score  70  // 眠二
#define A1score  30  // 活一

struct Chess
{
	int x, y;
	int score;
};

class Score
{
public:
	int** Board;
	int score;
	Chess ai_next_move;
	void QuickSortBuffer(Chess* Buffer_Score, int low, int high);
	void SortChoiceBuffer(Chess* possible_choice, int** Board, int id, int size);
	int GetPossibleChoice(Chess* possible_choice, int** Board, int id);
	int MiniMaxST(int id, int** Board, int depth, int alpha, int beta);

	int possible_choice[100][2];
	int size = 0;
	int neibor_R1(int x, int y, int** Board);
	int neibor_R2(int x, int y, int** Board);
	void PutChess(int x, int y, int id, int** Board);
	void RollBackChess(int x, int y, int** Board);
	Chess SleepEnemyP4(int** Board);
	Chess SleepEnemyA3(int** Board);
	Chess AIGotoC5(int** Board);
	Chess AIGotoA4(int** Board);

	Score(int** p);
	int getScore(int** Board);
	int numof_C5(int** Board, int id);
	int numof_A4(int** Board, int id);
	int numof_P4(int** Board, int id);
	int numof_A3(int** Board, int id);
	int numof_S3(int** Board, int id);
	int numof_A2(int** Board, int id);
	int numof_S2(int** Board, int id);
	int numof_A1(int** Board, int id);

};

