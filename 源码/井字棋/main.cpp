#include"head.h"
int chesselem[3][3];
//预设3*3的棋盘
int X, Y, count;
int WIN()//返回-1表示胜利，返回1表示失败
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (chesselem[i][0] == 1 && chesselem[i][1] == 1 && chesselem[i][2] == 1) return 1;
		if (chesselem[i][0] == -1 && chesselem[i][1] == -1 && chesselem[i][2] == -1) return -1;
	}
	//列比较
	for (i = 0; i < 3; i++)
	{
		if (chesselem[0][i] == 1 && chesselem[1][i] == 1 && chesselem[2][i] == 1) return 1;
		if (chesselem[0][i] == -1 && chesselem[1][i] == -1 && chesselem[2][i] == -1) return -1;
	}
	//行比较
	if ((chesselem[0][0] == 1 && chesselem[1][1] == 1 && chesselem[2][2] == 1) || (chesselem[2][0] == 1 && chesselem[1][1] == 1 && chesselem[0][2] == 1)) return 1;
	if ((chesselem[0][0] == -1 && chesselem[1][1] == -1 && chesselem[2][2] == -1) || (chesselem[2][0] == -1 && chesselem[1][1] == -1 && chesselem[0][2] == -1)) return -1;

	return 0;
}

int EVA()//打分函数，计算每一行、每一列、斜线中相连的棋子有多少个。
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
//进行α-β剪枝，获取接下来的最优路径
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
	if (maxn) if (flag > value) value = flag;		//判断状态 
	else if (flag < value) value = flag;
	return flag;
}

void Cinput()//坐标输入函数
{
	int x, y;
	while (true)
	{
		printf("\n请输入你想填入的坐标(X Y):");
		scanf_s("%d",&x);
		scanf_s("%d",&y);

		if (x > 0 && x < 4 && y > 0 && y < 4 && chesselem[x - 1][y - 1] == 0)
		{
			chesselem[x - 1][y - 1] = -1;
			break;
		}
		else printf("输入错误!\n");
	}
}

void ChessTable()//棋盘打印函数
{
	int i, j;

	printf("\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (chesselem[i][j] == 1) printf("○");
			if (chesselem[i][j] == 0) printf("□");
			if (chesselem[i][j] == -1) printf("×");
		}
		printf("\n");
	}
}

int Tchess()//井字棋运行主要程序
{
	int x, y, t;
	int m = -10086, value = -10086, d = 1;

	count = 0;
	memset(chesselem, 0, sizeof(chesselem));//初始化棋盘
	printf("棋盘:\n");
	ChessTable();//打印棋盘

	while (true)
	{
		printf("\n你想让谁执行第一步:\n1)玩家.  2)电脑.\n");
		scanf_s("%d",&t);
		if (t != 1 && t != 2)
		{
			getchar();//输入错误则继续读入
			printf_s("请输入1或2\n");
		}
		else break;
	}

	if (t == 1)//玩家先手
	{
		while (true)
		{
			Cinput();
			ChessTable();
			count++;
			EVA();//判断输赢
			if (Y == 0)
			{
				printf("\n平局!\n");
				return 0;
			}
			if (WIN() == -1)
			{
				printf("\n你赢了!\n");
				return 0;
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (chesselem[i][j] == 0)
					{
						chesselem[i][j] = 1;
						AlphaBeta(value, d, 1);		//运行α-β剪枝算法

						if (WIN() == 1)
						{
							printf("\n电脑将棋下在了:%d %d\n", i + 1, j + 1);
							ChessTable();
							printf("\n电脑赢了!\n");
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
			if (chesselem[x][y])	//判断玩家是否获胜
			{
				printf("\n你赢了!\n");
				return 0;
			}
			chesselem[x][y] = 1;

			value = -10086; m = -10086; d = 1;	//设定极大极小值
			printf("\n电脑将棋下在了:%d %d\n", x + 1, y + 1);
			ChessTable();
			count++;
			EVA();//判断胜负

			if (Y == 0)
			{
				printf("\n平局!\n");
				return 0;
			}
		}
	}
	else//电脑输入的条件
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
							printf("\n电脑将棋下在了:%d %d\n", i + 1, j + 1);
							ChessTable();
							printf("\n电脑赢了!\n");
							return 0;
						}
						//用状态的极大和极小判断哪一方胜利
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
			//思想同上
			value = -10086; m = -10086; d = 1;
			printf("\n电脑将棋下在了:%d %d\n", x + 1, y + 1);
			ChessTable();
			count++;
			EVA();

			if (X == 0)
			{
				printf("\n平局!\n");
				return 0;
			}

			Cinput();
			ChessTable();
			count++;
			EVA();

			if (X == 0)
			{
				printf("\n平局!\n");
				return 0;
			}

			if (WIN() == -1)
			{
				printf("\n你赢了!.\n");
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
		printf("\n再来一局?\n1)再来一局！.\t0)不玩了.\n");
		scanf_s("%d",&p);
		if (p != 1 && p != 2) getchar();
		if (p == 0) break;
	}
	return 0;
}