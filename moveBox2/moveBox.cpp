// moveBox.cpp : 推箱子
#include <iostream>
#include <list>
#include <vector>
#include <easyx.h>
#include <conio.h>

using namespace std;
struct Level  //地图关卡
{
	vector<vector<int>> data;//动态二维数组
	int x;  //人物x坐标
	int y;  //人物y坐标

};

class MoveBox
{
	Level level;  //动态二维数组
	int len = 600;
	int px;
	vector<IMAGE> image;

	//路:0B 墙:1B 箱子:10B 目的地:100B   目的地+箱子:110B
	//路:0 墙:1	箱子:2(1<<1)	目的地:4(1<<2)		
	//目的地+箱子:6(1<<1|1<<2)
	void init()
	{
		vector<vector<int>> gameMap =
		{
			{ 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 4, 0, 0, 1 },
			{ 1, 0, 0, 2, 0, 0, 1 },
			{ 1, 4, 2, 0, 2, 4, 1 },
			{ 1, 0, 0, 2, 0, 0, 1 },
			{ 1, 0, 0, 4, 0, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1 },
		};
		level.data = gameMap;
		level.x = 3;  //人物x坐标
		level.y = 3;  //人物y坐标
		px = len / level.data.size();
	}
	//加载图形
	void getRes()
	{
		image.resize(6);
		loadimage(&image[0], _T("res/player.png"), px, px);
		loadimage(&image[1], _T("res/box.png"), px, px);
		loadimage(&image[2], _T("res/end.png"), px, px);
		loadimage(&image[3], _T("res/bk.jpg"), len, len);
		loadimage(&image[4], _T("res/wall.png"), px, px);
		loadimage(&image[5], _T("res/go.png"), px, px);

	}

	//判断是否结束
	bool isWin()
	{
		for (int i = 0; i < level.data.size(); ++i)
		{
			for (int j = 0; j < level.data[i].size(); ++j)
			{
				if (level.data[i][j] == 4)
				{
					return false;
				}
			}
		}
		return true;
	}

	//绘制游戏
	void draw()
	{
		BeginBatchDraw();  //开始批量绘制
		putimage(0, 0, &image[3]);
		for (int i = 0; i < level.data.size(); ++i)
		{
			for (int j = 0; j < level.data[i].size(); ++j)
			{
				if (level.data[i][j] == 6) //箱子+目的地:6
				{
					putimage(j*px, i*px, &image[2]);
				}
				else if (level.data[i][j] == 4)	//目的地
				{
					putimage(j*px, i*px, &image[5]);
				}
				else if (level.data[i][j] == 2)  //箱子:2
				{
					putimage(j*px, i*px, &image[1]);
				}
				else if (level.data[i][j] == 1)  //墙
				{
					putimage(j*px, i*px, &image[4]);
				}
			}
		}
		putimage(level.x*px, level.y*px, &image[0]);
		EndBatchDraw();  //结束批量绘制
	}

	void move(int mx, int my)
	{
		int newX = level.x + mx;
		int newY = level.y + my;
		if (newX < 0 || newX >= level.data.size()
			|| newY < 0 || newY >= level.data[newX].size()
			|| level.data[newY][newX] == 1)
			return;

		if (level.data[newY][newX] == 0 || level.data[newY][newX] == 4)
		{
			level.y = newY;
			level.x = newX;
		}
		//箱子 010B  110B   100
		//		 2     6
		//  010 >> 001		110  >>  011&1    11&1  1  10&01  0
		else if ((level.data[newY][newX] >> 1) & 1) //前方是箱子
		{
			int moveX = level.x + mx * 2;
			int moveY = level.y + my * 2;
			if (moveX < 0 || moveX >= level.data.size()
				|| moveY < 0 || moveY >= level.data[moveX].size()
				|| level.data[moveY][moveX] == 1)
				return;

			if (level.data[moveY][moveX] == 0 || level.data[moveY][moveX] == 4)
			{
				//箱子位置零 110 -》 100  10 -》 0
				level.data[newY][newX] &= ~(size_t)(1 << 1);
				// 箱子位置1 101 ->  111    100 -> 110
				level.data[moveY][moveX] |= 1 << 1;

				level.x = newX;
				level.y = newY;
			}
		}
	}

	void control()
	{
		int key = _getch();
		int mx = 0, my = 0;
		switch (key)
		{
		case 'w':
		case 'W':
			my--;
			break;
		case 's':
		case 'S':
			my++;
			break;
		case 'a':
		case 'A':
			mx--;
			break;
		case 'd':
		case 'D':
			mx++;
			break;
		}
		move(mx, my);
	}
public:
	MoveBox()
	{
		init();
		getRes();
		initgraph(len, len);
	}
	void runGame()
	{
		while (true)
		{
			draw();
			control();

			if (isWin())
			{
				draw();
				MessageBox(GetForegroundWindow(), _T("恭喜过关"), _T("游戏结束"), 0);
				getchar();
				break;
			}
		}
	}
};
int main()
{
	MoveBox movebox;
	movebox.runGame();
	return 0;
}

