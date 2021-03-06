// 五子棋游戏

#include <easyx.h> //图形库文件
#include <stdio.h>

const int N = 13;	//棋盘的大小
int chessboard[N][N] = { 0 }; //储存棋盘数据 //0无棋 1黑棋 2白棋
int length = 700;//屏幕大小
int px;
bool isBlack = true; //是否是白棋
int isGameOver = false;

//初始化
void init()
{
	initgraph(length, length, SHOWCONSOLE);
	px = length / (N + 1);
	setbkcolor(0x3399cc);
	setlinecolor(0x0);
	memset(chessboard, 0, sizeof(chessboard));
}

bool isWin(int x, int y)
{
	if (chessboard[y][x] == 0)
	{
		return false;
	}
	int dir[][2] = { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, -1 } };
	for (int i = 0; i < 4; i++)
	{
		int count = 1;
		for (int j = 1; j < 5; j++)
		{

			int mx = x - dir[i][0] * j;
			int my = y - dir[i][1] * j;
			if (mx >= 0 && mx < N&&my >= 0 && my < N
				&& chessboard[my][mx] == chessboard[y][x])
			{
				count++;
			}
			mx = x + dir[i][0] * j;
			my = y + dir[i][1] * j;
			if (mx >= 0 && mx < N&&my >= 0 && my < N
				&&chessboard[my][mx] == chessboard[y][x])
			{
				count++;
			}
		}
		if (count >= 5)
		{
			return true;
		}
	}
	return false;
}



//绘制棋盘
void drawBorad()
{
	cleardevice();
	for (int i = 1; i <= N; i++)
	{
		line(px, px*i, length - px, i*px);
		line(px*i, px, i*px, length - px);
	}
	setfillcolor(0x0);
	solidcircle(3 * px, 3 * px, px / 8);
	solidcircle(3 * px, (N - 2)*px, px / 8);
	solidcircle((N - 2)*px, 3 * px, px / 8);
	solidcircle((N - 2)*px, (N - 2)*px, px / 8);
	solidcircle((N / 2 + 1)*px, (N / 2 + 1)*px, px / 8);

}

//绘制棋子
void drawPieces()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (chessboard[i][j] == 1) //画黑棋
			{
				setfillcolor(0x0);
				solidcircle((j + 1)*px, (i + 1)*px, px / 3);
			}
			else if (chessboard[i][j] == 2) //画白棋
			{
				setfillcolor(0xffffff);
				solidcircle((j + 1)*px, (i + 1)*px, px / 3);
			}
		}
	}
}

void draw()
{
	BeginBatchDraw();
	drawBorad();
	drawPieces();
	EndBatchDraw();
}

void play()
{
	MOUSEMSG msg = GetMouseMsg();
	int x = (msg.x - px / 2) / px;
	int y = (msg.y - px / 2) / px;

	if (msg.uMsg == WM_LBUTTONDOWN && 0 == chessboard[y][x])
	{
		chessboard[y][x] = isBlack ? 1 : 2;	
		if (isWin(x, y))
		{
			draw();
			if (isBlack)
				MessageBox(GetForegroundWindow(), _TEXT("黑棋胜利"), _TEXT("游戏结束"), MB_OK);
			else
				MessageBox(GetForegroundWindow(), _TEXT("白棋胜利"), _TEXT("游戏结束"), MB_OK);
			isGameOver = true;
		}
		isBlack = !isBlack;
	}
	
}

void runGame()
{
	init();//初始化数据
	while (true)
	{
		draw();	///绘制图形
		play(); ///玩家交互
		if (isGameOver)
		{
			isGameOver = false;
			memset(chessboard, 0, sizeof(chessboard));
			
		}
	}
}

int main()
{
	runGame();
	getchar();
}
