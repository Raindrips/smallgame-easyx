#define _CRT_SECURE_NO_WARNINGS
#include "Game_2048.h"
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <algorithm>


Game_2048::Game_2048()
{
	srand((unsigned int)time(NULL));
	initgraph(550, 550, SHOWCONSOLE);
}

int Game_2048::start()
{
	init();
	while (true)
	{
		updata();
		if (isGameOver())
		{
			sprintf(ea, "%d", score);
			if (MessageBox(GetHWnd(), ea, "是否再来一局", MB_YESNO) == IDYES)
			{
				init();
				updata();
			}
			else
			{
				exit(0);
			}
		}
	}
	system("pause");
	return 0;
}

void Game_2048::init()
{
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = 0;
		}
	}
	int x, y;
	//随机2个位置复制为初始位置
	for (int i = 0; i < 2; i++)
	{
		x = rand() % 4;
		y = rand() % 4;
		arr[x][y] = 2;
	}
}

void Game_2048::color(int i)
{

	switch (i)
	{
	case 0:
		setfillcolor(LIGHTGRAY);
		break;
	case 1:
		setfillcolor(BLUE);
		break;
	case 2:
		setfillcolor(GREEN);
		break;
	case 3:
		setfillcolor(CYAN);
		break;
	case 4:
		setfillcolor(RED);
		break;
	case 5:
		setfillcolor(MAGENTA);
		break;
	case 6:
		setfillcolor(LIGHTBLUE);
		break;
	case 7:
		setfillcolor(YELLOW);
		break;
	case 8:
		setfillcolor(LIGHTMAGENTA);
		break;
	case 9:
		setfillcolor(DARKGRAY);
		break;
	}
}

int Game_2048::check()
{
	int a = 0;
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			if (arr[i][j] == 0)
			{
				a++;
			}
		}
	}
	return a;
}

void Game_2048::swit(int x, int y, int at)
{
	int IQ = 0;
	if (at < 10)
	{
		settextstyle(80, 80, "楷体");
		IQ = at;
	}
	else if (at >= 10 && at < 100)
	{
		settextstyle(80, 40, "楷体");
		IQ = at / 10;
	}
	else if (at >= 100 && at < 1000)
	{
		settextstyle(80, 20, "楷体");
		IQ = at / 100;
	}
	else if (at >= 1000 && at < 10000)
	{
		settextstyle(80, 10, "楷体");
		IQ = at / 1000;
	}
	else if (at >= 10000 && at < 100000)
	{
		settextstyle(80, 5, "楷体");
		IQ = at / 10000;
	}

	if (at == 0)
	{
		setfillcolor(LIGHTGRAY);
		solidroundrect(x, y, x + 100, y + 100, 30, 30);
	}
	else
	{
		color(IQ);
		solidroundrect(x, y, x + 100, y + 100, 30, 30);
		char et[30] = " ";
		sprintf(et, "%d", at);
		outtextxy(x + 10, y + 10, et);
	}
}

int Game_2048::step(int x, int y, int mx, int my)
{
	int m = 0;
	int dx = x;
	int dy = y;

	while (true) {
		dx += mx;
		dy += my;

		if (!inArea(dx, dy))
		{
			break;
		}
		if (arr[dy][dx] == 0)
		{
			m++;
		}
	}
	return m;
}

int Game_2048::Move(int x, int y)
{
	int m = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[j][i] != 0)
			{
				m = step(i, j, x, y);
				std::swap(arr[j + m * y][i + m * x], arr[j][i]);
				mergeNum(arr[j + m * y + y][i + m * x + x], arr[j + m * y][i + m * x]);
			}
		}
	}
	return 0;
}

void Game_2048::random()
{
	int x = 0, y = 0;
	while (true)
	{
		x = rand() % 4;
		y = rand() % 4;
		if (arr[x][y] == 0)
		{
			arr[x][y] = 2;
			break;
		}
	}
}

bool Game_2048::isGameOver()
{
	int end = 0;
	int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr[i][j] != 0)
			{
				int flag = true;
				for (int z = 0; z < 4; z++)
				{
					int dx = dir[z][1] + arr[i][j];
					int dy = dir[z][0] + arr[i][j];
					if (!inArea(dx, dy))
						continue;
					if (arr[i][j] == arr[dy][dx])
					{
						flag = false;
						break;
					}
				}
				//4个方向都不等
				if (flag)
					end++;
			}
		}
	}
	return end == 16;
}

int Game_2048::keyDown()
{
	int fenshu = 0;
loop:
	char whpar = _getch();
	switch (whpar)
	{
	case 'w':
	case 'W':

		//fenshu += UP();
		Move(0, -1);
		break;
	case 'a':
	case 'A':
		Move(-1, 0);
		break;
	case 's':
	case 'S':
		Move(0, 1);
		break;
	case 'd':
	case 'D':
		Move(1, 0);
		break;
	default:
		goto loop;
		break;
	}
	return fenshu;
}

void Game_2048::draw()
{

	setbkcolor(DARKGRAY);
	setbkmode(TRANSPARENT);
	settextstyle(30, 30, "楷体");
	BeginBatchDraw();
	cleardevice();
	if (check() != 0)
	{
		random();
	}
	
	sprintf(ea, "%d", score);
	outtextxy(200, 0, ea);
	text();
	EndBatchDraw();
}

void Game_2048::text()
{
	//system("cls");
	int x, y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			x = i * 120 + 40;
			y = j * 120 + 40;
			swit(x, y, arr[j][i]);
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

void Game_2048::updata()
{
	draw();
	keyDown();
}

bool Game_2048::inArea(int x, int y)
{
	return !(x >= 4 || x < 0 || y >= 4 || y < 0);
}

void Game_2048::mergeNum(int& v1, int& v2)
{
	if (v1 == v2)
	{
		v1 *= 2;
		v2 = 0;
	}
}
