#pragma once
#define C5score  135000   // 连五
#define A4score  25000   // 活四
#define P4score  5201   // 冲四
#define A3score  4991   // 活三
#define S3score  410  // 眠三
#define A2score  450  // 活二
#define S2score  70  // 眠二
#define A1score  30  // 活一

class Score
{
public:
	int size;
	int** Board;
	Score(int** p, int size);
	int getScore(int** Board, int id);
	int Judgeif_A3(int x, int y, int id) {};
	int Score::numof_C5(int** Board, int id);
	int Score::numof_A4(int** Board, int id);
	int Score::numof_P4(int** Board, int id);
	int Score::numof_A3(int** Board, int id);
	int Score::numof_S3(int** Board, int id);
	int Score::numof_A2(int** Board, int id);
	int Score::numof_S2(int** Board, int id);
	int Score::numof_A1(int** Board, int id);

	int Score::numof_C5_col(int** Board, int id);
	int Score::numof_C5_row(int** Board, int id);
	int Score::numof_C5_left(int** Board, int id);
	int Score::numof_C5_right(int** Board, int id);
	int Score::numof_A4_col(int** Board, int id);
	int Score::numof_A4_row(int** Board, int id);
	int Score::numof_A4_left(int** Board, int id);
	int Score::numof_A4_right(int** Board, int id);
	int Score::numof_P4_col(int** Board, int id);
	int Score::numof_P4_row(int** Board, int id);
	int Score::numof_P4_left(int** Board, int id);
	int Score::numof_P4_right(int** Board, int id);
	int Score::numof_A3_col(int** Board, int id);
	int Score::numof_A3_row(int** Board, int id);
	int Score::numof_A3_left(int** Board, int id);
	int Score::numof_A3_right(int** Board, int id);
	int Score::numof_S3_col(int** Board, int id);
	int Score::numof_S3_row(int** Board, int id);
	int Score::numof_S3_left(int** Board, int id);
	int Score::numof_S3_right(int** Board, int id);
	int Score::numof_A2_col(int** Board, int id);
	int Score::numof_A2_row(int** Board, int id);
	int Score::numof_A2_left(int** Board, int id);
	int Score::numof_A2_right(int** Board, int id);
	int Score::numof_S2_col(int** Board, int id);
	int Score::numof_S2_row(int** Board, int id);
	int Score::numof_S2_left(int** Board, int id);
	int Score::numof_S2_right(int** Board, int id);
	int Score::numof_A1_col(int** Board, int id);
	int Score::numof_A1_row(int** Board, int id);
	int Score::numof_A1_left(int** Board, int id);
	int Score::numof_A1_right(int** Board, int id);
};

