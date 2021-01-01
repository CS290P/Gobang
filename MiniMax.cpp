#include "pch.h"
#include "MiniMax.h"
#include "Score.h"
#include "ChosePlace.h"

int MiniMax::GetPossibleChoice(Chess* possible_choice,int** Board) {
	int cnt = 0;
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			if (cnt >= 225)
				break;
			if (neibor_R1(i, j, Board)&&Board[i][j]==0) {
				possible_choice[cnt].x = i;
				possible_choice[cnt].y = j;
				cnt++;
			}
		}
		if (cnt >= 225)
			break;
	}
	return cnt;
}

int  MiniMax::MiniMaxST(int id,int** Board, int depth, int alpha, int beta) {
	if (depth > 4)
		return 0;
	int score;
	Chess possible_choice[225];
	int x, y;
	Chess* p_now = possible_choice;
	Chess* p_end = possible_choice + GetPossibleChoice(possible_choice, Board);
	if (id == 1) {   //AI的轮次
		while (p_now != p_end) {
			x = p_now->x;
			y = p_now->y;
			PutChess(x, y, 1, Board);
			score = MiniMaxST(-1, Board, depth + 1, alpha, beta);
			RollBackChess(x, y, Board);
			if (score > alpha)			// 对于AI，更新极大值
			{
				if (!depth)				// 在第0层进行搜索时，还需同时更新最优选择的坐标
				{
					ai_next_move.x = x;  //更新决定下的棋
					ai_next_move.y = y;
				}
				alpha = score;    
			}
			if (alpha >= beta)   		// 进行 Alpha 剪枝
			{
				return alpha;
			}
			if (depth && alpha >= C5score)		// 必胜剪枝
				return alpha;
			++p_now;
		}
	}
	else if (id == -1) {
		while (p_now != p_end) {
			x = p_now->x;
			y = p_now->y;
			PutChess(x, y, -1, Board);
			score = MiniMaxST(1, Board, depth + 1, alpha, beta);
			RollBackChess(x, y, Board);
			if (score < beta)			// 对于玩家，更新极小值
			{
				beta = score;
			}
			if (alpha >= beta)   		// 进行 Beta 剪枝
			{
				return beta;
			}
			if (beta <= -C5score)		// 必败剪枝
				return beta;
			++p_now;
		}
		return beta;// 玩家从所有落子情况中选择分数最低值
	}
}