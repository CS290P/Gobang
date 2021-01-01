#include "pch.h"
#include "Score.h"

Score::Score(int** p, int size) {
	this->size = size;
	Board = p;
	// + - 0
}

int Score::getScore(int** Board, int id) { 
	// id= 1  +  id= -1 - 
	int score = 0;
	if (numof_C5(Board,1)) {
		return 135000;   //�Ѿ�Ӯ��
	}
	if (numof_C5(Board, -1)) {
		return -135000;   //�Ѿ�Ӯ��
	}
	//�����A4����һ�����Լ��±�ʤ���Է�û�����塢���ġ����ģ���ô�Լ���ʤ
	score = 25000 * numof_A4(Board, 1) - 25000 * numof_A4(Board, -1) + 5201 * numof_P4(Board, 1) - 5201 * numof_P4(Board, -1) + 4991 * numof_A3(Board, 1) - 4991 * numof_A3(Board, -1) + 410 * numof_S3(Board, 1)
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

int Score::numof_C5_col(int** Board, int id) {
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
	return 0;
}

int Score::numof_C5_row(int** Board, int id) {
	int cnt = 0;
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
	return 0;
}

int Score::numof_C5_left(int** Board, int id) //�����µ����� ����Ʋ���Ʋ
{
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id)
				return 1;
		}
	}
	return 0;
}

int Score::numof_C5_right(int** Board, int id)   //�����µ�����
{
	for (int i = 0; i <= 10; i++) {
		for (int j = 4; j < 15; j++) {
			if (Board[i][j] == id && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id)
				return 1;
		}
	}
	return 0;
}

int Score::numof_A4_col(int** Board, int id) {
	int numof_A4 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == id && Board[i][j + 5] == 0)
				numof_A4++;
		}
	}
	return numof_A4;
}

int Score::numof_A4_row(int** Board, int id) {
	int numof_A4 = 0;
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == id && Board[i + 5][j] == 0)
				numof_A4++;
		}
	}
	return numof_A4;
}

int Score::numof_A4_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_A4 = 0;
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == id && Board[i + 5][j + 5] == 0)
				numof_A4++;
		}
	}
	return numof_A4;
}

int Score::numof_A4_right(int** Board, int id) {
	int numof_A4 = 0;
	for (int i = 0; i <= 9; i++) {
		for (int j = 5; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == id && Board[i + 3][j - 3] == id && Board[i + 4][j - 4] == id && Board[i + 5][j - 5] == 0)
				numof_A4++;
		}
	}
	return numof_A4++;
}

int Score::numof_P4_col(int** Board, int id) {
	int numof_P4 = 0;
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
	return numof_P4;
}

int Score::numof_P4_row(int** Board, int id) {
	int numof_P4 = 0;
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
	return numof_P4;
}

int Score::numof_P4_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_P4 = 0;
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
	return numof_P4;
}

int Score::numof_P4_right(int** Board, int id) {
	int numof_P4 = 0;
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
	return numof_P4++;
}

int Score::numof_A3_col(int** Board, int id) {     //lookahead �������
	int numof_A3 = 0;
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
	return numof_A3;
}

int Score::numof_A3_row(int** Board, int id) {    //lookahead �������
	int numof_A3 = 0;
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
	return numof_A3;
}

int Score::numof_A3_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_A3 = 0;
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
	return numof_A3;
}

int Score::numof_A3_right(int** Board, int id) {
	int numof_A3 = 0;
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

int Score::numof_S3_col(int** Board, int id) {
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
	return numof_S3;
}

int Score::numof_S3_row(int** Board, int id) {
	int numof_S3 = 0;
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
	return numof_S3;
}

int Score::numof_S3_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_S3 = 0;
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
	return numof_S3;
}

int Score::numof_S3_right(int** Board, int id) {
	int numof_S3 = 0;
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

int Score::numof_A2_col(int** Board, int id) {     //lookahead �������
	int numof_A2 = 0;
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
	return numof_A2;
}

int Score::numof_A2_row(int** Board, int id) {    //lookahead �������
	int numof_A2 = 0;
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
	return numof_A2;
}

int Score::numof_A2_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_A2 = 0;
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
	return numof_A2;
}

int Score::numof_A2_right(int** Board, int id) {
	int numof_A2 = 0;
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

int Score::numof_S2_col(int** Board, int id) {     //lookahead �������
	int numof_S2 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 11; j++) {
			if (Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == id && Board[i][j + 3] == 0 && Board[i][j + 4] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == 0 && Board[i][j + 2] == id && Board[i][j + 3] == id && Board[i][j + 4] == -id
				|| Board[i][j] == -id && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == 0
				|| Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0 && Board[i][j + 3] == id && Board[i][j + 4] == -id)
				numof_S2++;
		}
	}
	return numof_S2;
}

int Score::numof_S2_row(int** Board, int id) {    //lookahead �������
	int numof_S2 = 0;
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 11; i++) {
			if (Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == id && Board[i + 3][j] == 0 && Board[i + 4][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == 0 && Board[i + 2][j] == id && Board[i + 3][j] == id && Board[i + 4][j] == -id
				|| Board[i][j] == -id && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == 0
				|| Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0 && Board[i + 3][j] == id && Board[i + 4][j] == -id)
				numof_S2++;
		}
	}
	return numof_S2;
}

int Score::numof_S2_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_S2 = 0;
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == 0 && Board[i + 4][j + 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 2] == id && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == -id
				|| Board[i][j] == -id && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == 0
				|| Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0 && Board[i + 3][j + 3] == id && Board[i + 4][j + 4] == -id)
				numof_S2++;
		}
	}
	return numof_S2;
}

int Score::numof_S2_right(int** Board, int id) {
	int numof_S2 = 0;
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

int Score::numof_A1_col(int** Board, int id) {     //lookahead �������
	int numof_A1 = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			if (Board[i][j] == 0 && Board[i][j + 1] == id && Board[i][j + 2] == 0)
				numof_A1++;
		}
	}
	return numof_A1;
}

int Score::numof_A1_row(int** Board, int id) {    //lookahead �������
	int numof_A1 = 0;
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 13; i++) {
			if (Board[i][j] == 0 && Board[i + 1][j] == id && Board[i + 2][j] == 0)
				numof_A1++;
		}
	}
	return numof_A1;
}

int Score::numof_A1_left(int** Board, int id) {   //�����µ����� ����Ʋ���Ʋ
	int numof_A1 = 0;
	for (int i = 0; i <= 12; i++) {
		for (int j = 0; j <= 12; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j + 1] == id && Board[i + 2][j + 2] == 0)
				numof_A1++;
		}
	}
	return numof_A1;
}

int Score::numof_A1_right(int** Board, int id) {
	int numof_A1 = 0;
	for (int i = 0; i <= 12; i++) {
		for (int j = 2; j < 15; j++) {
			if (Board[i][j] == 0 && Board[i + 1][j - 1] == id && Board[i + 2][j - 2] == 0)
				numof_A1++;
		}
	}
	return numof_A1++;
}