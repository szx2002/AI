#include"head.h"
int chesselem[3][3];
//Ԥ��3*3������
int X, Y, count;
int WIN()//����-1��ʾʤ��������1��ʾʧ��
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (chesselem[i][0] == 1 && chesselem[i][1] == 1 && chesselem[i][2] == 1) return 1;
		if (chesselem[i][0] == -1 && chesselem[i][1] == -1 && chesselem[i][2] == -1) return -1;
	}
	//�бȽ�
	for (i = 0; i < 3; i++)
	{
		if (chesselem[0][i] == 1 && chesselem[1][i] == 1 && chesselem[2][i] == 1) return 1;
		if (chesselem[0][i] == -1 && chesselem[1][i] == -1 && chesselem[2][i] == -1) return -1;
	}
	//�бȽ�
	if ((chesselem[0][0] == 1 && chesselem[1][1] == 1 && chesselem[2][2] == 1) || (chesselem[2][0] == 1 && chesselem[1][1] == 1 && chesselem[0][2] == 1)) return 1;
	if ((chesselem[0][0] == -1 && chesselem[1][1] == -1 && chesselem[2][2] == -1) || (chesselem[2][0] == -1 && chesselem[1][1] == -1 && chesselem[0][2] == -1)) return -1;

	return 0;
}

int EVA()//��ֺ���������ÿһ�С�ÿһ�С�б���������������ж��ٸ���
{
	int i, j, t[3][3];

	X = Y = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (chesselem[i][j] == 0) t[i][j] = 1;
			else t[i][j] = chesselem[i][j];
		}
	}

	for (i = 0; i < 3; i++) X += (t[i][0] + t[i][1] + t[i][2]) / 3;

	for (i = 0; i < 3; i++) X += (t[0][i] + t[1][i] + t[2][i]) / 3;

	X += (t[0][0] + 2*t[1][1] + t[2][2] + t[2][0] + t[0][2]) / 3;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (chesselem[i][j] == 0) t[i][j] = -1;
			else t[i][j] = chesselem[i][j];
		}
	}


	for (i = 0; i < 3; i++) Y += (t[i][0] + t[i][1] + t[i][2]) / 3;

	for (i = 0; i < 3; i++) Y += (t[0][i] + t[1][i] + t[2][i]) / 3;

	Y += (t[0][0] + 2*t[1][1] + t[2][2] + t[2][0] + t[0][2]) / 3;

	return X + Y;
}

int AlphaBeta(int& value, int d, bool maxn)
//���Ц�-�¼�֦����ȡ������������·��
{
	bool trim = false;
	int i, j, flag, t;

	if (d == 3 || d + count == 9) return EVA();

	if (WIN() == 1)
	{
		value = 10086;
		return 0;
	}

	if (maxn) flag = 10086;
	else flag = -10086;
	for (i = 0; i < 3 && !trim; i++)
	{
		for (j = 0; j < 3 && !trim; j++)
		{
			if (chesselem[i][j] == 0)
			{
				if (maxn)
				{
					chesselem[i][j] = -1;

					if (WIN() == -1) t = -10086;
					else t = AlphaBeta(flag, d + 1, !maxn);

					if (t < flag) flag = t;
					if (flag <= value) trim = true;
				}
				else
				{
					chesselem[i][j] = 1;

					if (WIN() == 1) t = 10086;
					else t = AlphaBeta(flag, d + 1, !maxn);

					if (t > flag) flag = t;
					if (flag >= value) trim = true;

				}
				chesselem[i][j] = 0;
			}
		}
	}
	if (maxn) if (flag > value) value = flag;		//�ж�״̬ 
	else if (flag < value) value = flag;
	return flag;
}

void Cinput()//�������뺯��
{
	int x, y;
	while (true)
	{
		printf("\n�������������������(X Y):");
		scanf_s("%d",&x);
		scanf_s("%d",&y);

		if (x > 0 && x < 4 && y > 0 && y < 4 && chesselem[x - 1][y - 1] == 0)
		{
			chesselem[x - 1][y - 1] = -1;
			break;
		}
		else printf("�������!\n");
	}
}

void ChessTable()//���̴�ӡ����
{
	int i, j;

	printf("\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (chesselem[i][j] == 1) printf("��");
			if (chesselem[i][j] == 0) printf("��");
			if (chesselem[i][j] == -1) printf("��");
		}
		printf("\n");
	}
}

int Tchess()//������������Ҫ����
{
	int x, y, t;
	int m = -10086, value = -10086, d = 1;

	count = 0;
	memset(chesselem, 0, sizeof(chesselem));//��ʼ������
	printf("����:\n");
	ChessTable();//��ӡ����

	while (true)
	{
		printf("\n������˭ִ�е�һ��:\n1)���.  2)����.\n");
		scanf_s("%d",&t);
		if (t != 1 && t != 2)
		{
			getchar();//����������������
			printf_s("������1��2\n");
		}
		else break;
	}

	if (t == 1)//�������
	{
		while (true)
		{
			Cinput();
			ChessTable();
			count++;
			EVA();//�ж���Ӯ
			if (Y == 0)
			{
				printf("\nƽ��!\n");
				return 0;
			}
			if (WIN() == -1)
			{
				printf("\n��Ӯ��!\n");
				return 0;
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (chesselem[i][j] == 0)
					{
						chesselem[i][j] = 1;
						AlphaBeta(value, d, 1);		//���Ц�-�¼�֦�㷨

						if (WIN() == 1)
						{
							printf("\n���Խ���������:%d %d\n", i + 1, j + 1);
							ChessTable();
							printf("\n����Ӯ��!\n");
							return 0;
						}

						if (value > m)
						{
							m = value;
							x = i;
							y = j;
						}
						value = -10086;
						chesselem[i][j] = 0;
					}
				}
			}
			if (chesselem[x][y])	//�ж�����Ƿ��ʤ
			{
				printf("\n��Ӯ��!\n");
				return 0;
			}
			chesselem[x][y] = 1;

			value = -10086; m = -10086; d = 1;	//�趨����Сֵ
			printf("\n���Խ���������:%d %d\n", x + 1, y + 1);
			ChessTable();
			count++;
			EVA();//�ж�ʤ��

			if (Y == 0)
			{
				printf("\nƽ��!\n");
				return 0;
			}
		}
	}
	else//�������������
	{
		while (true)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (chesselem[i][j] == 0)
					{
						chesselem[i][j] = 1;
						AlphaBeta(value, d, 1);
						if (WIN() == 1)
						{
							printf("\n���Խ���������:%d %d\n", i + 1, j + 1);
							ChessTable();
							printf("\n����Ӯ��!\n");
							return 0;
						}
						//��״̬�ļ���ͼ�С�ж���һ��ʤ��
						if (value > m)
						{
							m = value;
							x = i; 
							y = j;
						}
						value = -10086;
						chesselem[i][j] = 0;
					}
				}
			}
			chesselem[x][y] = 1;
			//˼��ͬ��
			value = -10086; m = -10086; d = 1;
			printf("\n���Խ���������:%d %d\n", x + 1, y + 1);
			ChessTable();
			count++;
			EVA();

			if (X == 0)
			{
				printf("\nƽ��!\n");
				return 0;
			}

			Cinput();
			ChessTable();
			count++;
			EVA();

			if (X == 0)
			{
				printf("\nƽ��!\n");
				return 0;
			}

			if (WIN() == -1)
			{
				printf("\n��Ӯ��!.\n");
				return 0;
			}
		}
	}

	return 0;
}

int main()
{
	using namespace std;
	int p;
	while (true)
	{
		Tchess();
		printf("\n����һ��?\n1)����һ�֣�.\t0)������.\n");
		scanf_s("%d",&p);
		if (p != 1 && p != 2) getchar();
		if (p == 0) break;
	}
	return 0;
}