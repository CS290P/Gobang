#include "pch.h"
#include "Score.h"

Score::Score(int** p) {
	//this->size = size;
	Board = p;
}

void Score::QuickSortBuffer(Chess* possible_choice, int low, int high) {  //������һ����score�������� Ϊ����һ���ֲ��Ż�Buffer size�Ĵ���
	int i, j, pivot;
	if (low >= high)
		return;
	else if (low < high) {
		i = low, j = high;
		pivot = possible_choice[low].score;
		while (i < j) {
			while (possible_choice[j].score <= pivot && i < j)   //�������� ���������ǰ��
				j--;
			if (i < j)
				possible_choice[i] = possible_choice[j];
			while (possible_choice[i].score >= pivot && i < j)
				i++;
			if (i < j)
				possible_choice[j] = possible_choice[i];
		}
		possible_choice[i].score = pivot;
		QuickSortBuffer(possible_choice, low, i - 1);
		QuickSortBuffer(possible_choice, i + 1, high);
	}
}

void Score::SortChoiceBuffer(Chess* possible_choice, int** Board, int id, int size) {
	int* Buffer_Socre;
	for (int i = 0; i < size; i++) {
		int x = possible_choice[i].x;
		int y = possible_choice[i].y;
		PutChess(x, y, id, Board);
		possible_choice[i].score = getScore(Board);
		RollBackChess(x, y, Board);
	}
	QuickSortBuffer(possible_choice, 0, size - 1);
}

int Score::GetPossibleChoice(Chess* possible_choice, int** Board, int id) {  //����һ���п����µ���װ��possible_choice id��Ϊ���򴫽�����
	int cnt = 0;
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			/*���� һ������Χ1��������ǿ����µĵ� ����������ֵ����뻹�ǻ������Ӵ� ������һ���ֲ��Ż����� Buffer�����Ӵ�ʱ����ȡ�ֲ����ŵ�40��
			���ݲ��� Ŀǰ��10�����4��MiniMax����Ҫ7-8s ���ܻ������*/
			if (neibor_R1(i, j, Board) && Board[i][j] == 0) {
				possible_choice[cnt].x = i;
				possible_choice[cnt].y = j;
				cnt++;
			}
		}
	}
	if (cnt >= 20) {
		SortChoiceBuffer(possible_choice, Board, id, cnt);
		cnt = 20;
	}
	return cnt;
}

int Score::MiniMaxST(int id, int** Board, int depth, int alpha, int beta) {
	if (depth > 4)
		return getScore(Board);
	int score;
	Chess possible_choice[225];
	int x, y;
	Chess* p_now = possible_choice;
	Chess* p_end = possible_choice + GetPossibleChoice(possible_choice, Board, id) - 1;
	if (id == 1) {   //AI���ִ�
		while (p_now != p_end) {
			x = p_now->x;
			y = p_now->y;
			PutChess(x, y, 1, Board);
			score = MiniMaxST(-1, Board, depth + 1, alpha, beta);
			RollBackChess(x, y, Board);
			if (score > alpha)			// ����AI�����¼���ֵ
			{
				if (!depth)				// �ڵ�0���������ʱ������ͬʱ��������ѡ�������
				{
					ai_next_move.x = x;  //���¾����µ���
					ai_next_move.y = y;
				}
				alpha = score;
			}
			if (alpha >= beta)   		// ���� Alpha ��֦
			{
				return alpha;
			}
			if (depth && alpha >= C5score)		// ��ʤ��֦
				return alpha;
			++p_now;
		}
		return alpha;
	}
	else if (id == -1) {
		while (p_now != p_end) {
			x = p_now->x;
			y = p_now->y;
			PutChess(x, y, -1, Board);
			score = MiniMaxST(1, Board, depth + 1, alpha, beta);
			RollBackChess(x, y, Board);
			if (score < beta)			// ������ң����¼�Сֵ
			{
				beta = score;
			}
			if (alpha >= beta)   		// ���� Beta ��֦
			{
				return beta;
			}
			if (beta <= -C5score)		// �ذܼ�֦
				return beta;
			++p_now;
		}
		return beta;// ��Ҵ��������������ѡ��������ֵ
	}
}

int Score::neibor_R1(int x, int y, int** Board) {
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

int Score::neibor_R2(int x, int y, int** Board) {
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

void Score::PutChess(int x, int y, int id, int** Board) {
	if (Board[x][y] != 0)
		return;
	else if (Board[x][y] == 0)
		Board[x][y] = id;
	return;
}

void Score::RollBackChess(int x, int y, int** Board) {
	Board[x][y] = 0;
	return;
}

Chess Score::SleepEnemyP4(int** Board) {
	Chess next;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] == 0) {
				PutChess(i, j, 1, Board);
				if (numof_P4(Board, -1) == 0) {
					next.x = i;
					next.y = j;
					RollBackChess(i, j, Board);
					break;
				}
				RollBackChess(i, j, Board);
			}
		}
	}
	return next;
}

Chess Score::SleepEnemyA3(int** Board) {
	Chess next;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] == 0) {
				PutChess(i, j, 1, Board);
				if (numof_A3(Board, -1) == 0) {
					next.x = i;
					next.y = j;
					RollBackChess(i, j, Board);
					break;
				}
				RollBackChess(i, j, Board);
			}
		}
	}
	return next;
}

Chess Score::AIGotoC5(int** Board) {
	Chess next;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] == 0) {
				PutChess(i, j, 1, Board);
				if (numof_C5(Board, 1) == 1) {
					next.x = i;
					next.y = j;
					RollBackChess(i, j, Board);
					break;
				}
				RollBackChess(i, j, Board);
			}
		}
	}
	return next;
}

Chess Score::AIGotoA4(int** Board) {
	Chess next;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] == 0) {
				PutChess(i, j, 1, Board);
				if (numof_A4(Board, 1) == 1) {
					next.x = i;
					next.y = j;
					RollBackChess(i, j, Board);
					break;
				}
				RollBackChess(i, j, Board);
			}
		}
	}
	return next;
}

int Score::getScore(int** Board) {
	// id= 1  +  id= -1 - 
	int score = 0;
	//if (numof_C5(Board, 1)) {
	//	return 135000;   //�Ѿ�Ӯ��
	//}
	//if (numof_C5(Board, -1)) {
	//	return -135000;   //�Ѿ�Ӯ��
	//}
	//�����A4����һ�����Լ��±�ʤ���Է�û�����塢���ġ����ģ���ô�Լ���ʤ
	score = numof_C5(Board, 1) * 135000 - numof_C5(Board, -1) * 135000 + 25000 * numof_A4(Board, 1) - 25000 * numof_A4(Board, -1) + 5201 * numof_P4(Board, 1) - 5201 * numof_P4(Board, -1) + 4991 * numof_A3(Board, 1) - 4991 * numof_A3(Board, -1) + 410 * numof_S3(Board, 1)
		- 410 * numof_S3(Board, -1) + 450 * numof_A2(Board, 1) - 450 * numof_A2(Board, -1) + 70 * numof_S2(Board, 1) - 70 * numof_S2(Board, -1) + 30 * numof_A1(Board, 1) - 30 * numof_A1(Board, -1);
	return score;
}

int Score::numof_C5(int** Board, int id) {
	int cnt = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] == id)
				cnt++;
			else
				cnt = 0;
			if (cnt == 5)
				return 1;    //if have C5, return, already  win
		}
	}
	cnt = 0;
	for (int j = 0; j > 15; j++) {
		for (int i = 0; i < 15; i++) {
			if (Board[i][j] == id)
				cnt++;
			else
				cnt = 0;
			if (cnt == 5)
				return 1;    //if have C5, return, already  win
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id)
				return 1;
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id)
				return 1;
		}
	}
	return 0;
}

int Score::numof_A4(int** Board, int id)  //�Ѻ���Ʋ��ȫ�����Ͻ��� д������ֱ�ӵ��û��㣿��Maybe
{
	int numof_A4 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == 0)
				numof_A4++;
		}
	}
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == 0)
				numof_A4++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0)
				numof_A4++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0)
				numof_A4++;
		}
	}
	return numof_A4;
}

int Score::numof_P4(int** Board, int id) {
	int numof_P4 = 0;
	//��
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == -id
				|| Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == 0)
				numof_P4++;
		}
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == id && Board[i][j + 1] == 0 && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id
				|| Board[i][j] == id && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == id
				|| Board[i][j] == id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == id)
				numof_P4++;
		}
	}
	//��
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == -id
				|| Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == 0)
				numof_P4++;
		}
		for (int i = 0; i <= 10; i++) {
			if (Board[i][j] == id && Board[i + 1][j] == 0 && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id
				|| Board[i][j] == id && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == id
				|| Board[i][j] == id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == id)
				numof_P4++;
		}
	}
	//Ʋ
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == -id)
				numof_P4++;
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == id && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id
				|| Board[i][j] == id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id
				|| Board[i][j] == id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == id)
				numof_P4++;
		}
	}
	//��
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == -id)
				numof_P4++;
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == id && Board[i + 1][j - 1] == 0 && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id
				|| Board[i][j] == id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id
				|| Board[i][j] == id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == id)
				numof_P4++;
		}
	}
	return numof_P4;
}

int Score::numof_A3(int** Board, int id) {
	int numof_A3 = 0;
	//��
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 11; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == 0)
				numof_A3++;
		}
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == id && Board[i][j + 5] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == 0)
				numof_A3++;
		}
	}
	//��
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 11; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == 0)
				numof_A3++;
		}
		for (int i = 0; i < 10; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == id && Board[i + 5][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == 0)
				numof_A3++;
		}
	}
	//Ʋ
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == 0)
				numof_A3++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0)
				numof_A3++;
		}
	}
	//��
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == 0)
				numof_A3++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0)
				numof_A3++;
		}
	}
	return numof_A3++;
}

int Score::numof_S3(int** Board, int id) {
	int numof_S3 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == 0 && Board[i][j + 5] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == 0 && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == -id
				|| Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == 0
				|| Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == id && Board[i][j + 5] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == -id
				|| Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == id && Board[i][j + 5] == -id)
				numof_S3++;
		}
	}
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == 0 && Board[i + 5][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == 0 && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == -id
				|| Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == 0
				|| Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == id && Board[i + 5][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == -id
				|| Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == id && Board[i + 5][j] == -id)
				numof_S3++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == 0 && Board[i + 5][j + 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == -id
				|| Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0
				|| Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == -id
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == -id)
				numof_S3++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == 0 && Board[i + 5][j - 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == 0 && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == -id
				|| Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0
				|| Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == -id
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == -id)
				numof_S3++;
		}
	}
	return numof_S3++;
}

int Score::numof_A2(int** Board, int id) {
	int numof_A2 = 0;
	//col
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 12; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0)
				numof_A2++;
		}
		for (int j = 0; j < 11; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == 0)
				numof_A2++;
		}
	}
	//row
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 12; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0)
				numof_A2++;
		}
		for (int i = 0; i < 11; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == 0)
				numof_A2++;
		}
	}
	//left
	for (int i = 0; i <= 11; i++) {
		for (int j = 0; j <= 11; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0)
				numof_A2++;
		}
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == 0)
				numof_A2++;
		}
	}
	//right
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == 0)
				numof_A2++;
		}
	}
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0)
				numof_A2++;
		}
	}
	return numof_A2++;
}

int Score::numof_S2(int** Board, int id) {
	int numof_S2 = 0;
	//col
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 11; j++) {
			if (Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == 0 && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == -id
				|| Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == -id)
				numof_S2++;
		}
	}
	//row
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 11; i++) {
			if (Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == 0 && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == -id
				|| Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == -id)
				numof_S2++;
		}
	}
	//left
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == -id
				|| Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == -id)
				numof_S2++;
		}
	}
	//right
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == 0 && Board[i + 4][j - 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == 0 && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == -id
				|| Board[i][j] == -id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0 && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == -id)
				numof_S2++;
		}
	}
	return numof_S2++;
}

int Score::numof_A1(int** Board, int id) {
	int numof_A1 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0)
				numof_A1++;
		}
	}
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 13; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0)
				numof_A1++;
		}
	}
	for (int i = 0; i <= 12; i++) {
		for (int j = 0; j <= 12; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0)
				numof_A1++;
		}
	}
	for (int i = 0; i <= 12; i++) {
		for (int j = 2; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0)
				numof_A1++;
		}
	}
	return numof_A1++;
}
