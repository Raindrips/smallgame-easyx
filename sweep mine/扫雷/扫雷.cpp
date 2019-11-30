// 扫雷.cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "easyx.h"

//坐标结构体
struct Position
{
	int x;
	int y;
};

enum PNG
{
	flag = 9, mine, block, question, open
};
int length = 640;				//屏幕大小
const int N = 9;				//区块的长度
int size;
const int MAX_MINE = 10;		//雷的数量
struct Position mines[MAX_MINE];	//雷的数组

int map[N][N];				//未翻开的区域
int valueMap[N][N];			//已翻开区域的数据

IMAGE image[14];			//储存图形的结构体	
int dir[8][2] = {
	{ 0, 1 }, { 0, -1 }, {  1, 1 }, {  1, -1 },
	{ 1, 0 }, { -1, 0 }, { -1, 1 }, { -1, -1 }
}; //坐标的8个方向

bool isGameOver;	//是否游戏结束
bool isFirst;		//是否是第一次


//每个雷的附近加上数字
void generateNum(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		int zx = dir[i][1] + x;
		int zy = dir[i][0] + y;
		if (zx < 0 || zx >= N || zy < 0 || zy >= N || valueMap[zy][zx] == mine)
		{
			continue;
		}
		valueMap[zy][zx]++;
	}
}

//生成地雷
void random_mine()
{
	//雷的初始化
	for (int i = 0; i < MAX_MINE; i++)
	{
		valueMap[i / N][i % N] = mine;
	}
	//通过交换,打乱雷的顺序
	for (int i = 0; i < MAX_MINE; i++)
	{
		int x = rand() % N;     //rand 获取一个int类型的随机数
		int y = rand() % N;		//rand随机数,每次获取的都不是一样的
		//交换雷的位置
		int t = valueMap[i / N][i % N];
		valueMap[i / N][i % N] = valueMap[y][x];
		valueMap[y][x] = t;
	}
	//找到所有已经交换好雷的一个位置
	int p = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (valueMap[i][j] == mine)
			{
				mines[p].x = j;
				mines[p].y = i;
				p++;
				printf("mine(question:%d y:%d)\n", j, i);
				generateNum(j, i);
			}
		}
	}
}

//初始化地图
void init_map()
{
	//也可以用for循环
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] = block;
			valueMap[i][j] = 0;
		}
	}
	random_mine();
	isGameOver = false;  //游戏结束条件设置为false;
	isFirst = true;
}


//初识化图形
void init_image()
{
	initgraph(length, length, SHOWCONSOLE);
	size = length / N;		//计算图形的大小
	//导入图片
	loadimage(&image[0], _T("res/0.png"), size, size);
	loadimage(&image[1], _T("res/1.png"), size, size);
	loadimage(&image[2], _T("res/2.png"), size, size);
	loadimage(&image[3], _T("res/3.png"), size, size);
	loadimage(&image[4], _T("res/4.png"), size, size);
	loadimage(&image[5], _T("res/5.png"), size, size);
	loadimage(&image[6], _T("res/6.png"), size, size);
	loadimage(&image[7], _T("res/7.png"), size, size);
	loadimage(&image[8], _T("res/8.png"), size, size);

	loadimage(&image[flag], _T("res/flag.png"), size, size);
	loadimage(&image[mine], _T("res/mine.png"), size, size);
	loadimage(&image[block], _T("res/block.png"), size, size);
	loadimage(&image[question], _T("res/question.png"), size, size);

	srand(time(NULL));   //生成随机数种子


}

//初始化
void init()
{
	init_image();
	init_map();//初始化地图
}

//自动填充算法
void floodFill(int x, int y)
{
	//遍历8个方向
	for (int i = 0; i < 8; i++)
	{
		if (valueMap[y][x] == 0)  //递归的条件是,附近没有雷
		{
			int dx = dir[i][1] + x;
			int dy = dir[i][0] + y;
			if (dx < 0 || dx >= N || dy < 0 || dy >= N) //越界就忽略掉
			{
				continue;
			}
			if (map[dy][dx] == block)    //如果是没有打开的区块
			{
				map[dy][dx] = open;  //
				floodFill(dx, dy);  //递归调用
			}
		}
	}
}

//玩家交互的函数
void play()
{
	MOUSEMSG mouse = GetMouseMsg();  //获取鼠标信息
	int x = mouse.x / size;		//获取x的坐标轴
	int y = mouse.y / size;		//获取y的坐标轴
	if (mouse.uMsg == WM_LBUTTONDOWN)  //鼠标左键按下的消息
	{
		printf("left:(%d,%d)\n", x, y);
		//是区块或者是问号,进行打开
		if (map[y][x] == block || map[y][x] == question)
		{
			if (valueMap[y][x] == mine)
			{
				isGameOver = true;
			}
			map[y][x] = open;
			floodFill(x, y);
		}
	}
	if (mouse.uMsg == WM_RBUTTONDOWN)  //鼠标右键按下的消息
	{
		printf("right:(%d,%d)\n", x, y);
		if (map[y][x] == block)  //如果是区块,就变成旗帜
		{
			map[y][x] = flag;
		}
		else if (map[y][x] == flag)  //如果是旗帜,就变成问号
		{
			map[y][x] = question;
		}
		else if (map[y][x] == question)//如果是问号,就变成区块
		{
			map[y][x] = block;
		}
	}


}


//绘制图像
void draw()
{
	BeginBatchDraw();//批量绘制
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//printf("%2d ", valueMap[i][j]);
			switch (map[i][j])
			{
			case block:		//没有打开的图像
				putimage(j*size, i*size, &image[block]);
				break;
			case flag:     //旗帜
				putimage(j*size, i*size, &image[flag]);
				break;
			case question:			//问号?
				putimage(j*size, i*size, &image[question]);
				break;

			case open:	//表示翻开的区块
				switch (valueMap[i][j])
				{
				case mine:		//表示雷
					putimage(j*size, i*size, &image[mine]);
					break;
				case 0:
					putimage(j*size, i*size, &image[0]);
					break;
				case 1:
					putimage(j*size, i*size, &image[1]);
					break;
				case 2:
					putimage(j*size, i*size, &image[2]);
					break;
				case 3:
					putimage(j*size, i*size, &image[3]);
					break;
				case 4:
					putimage(j*size, i*size, &image[4]);
					break;
				case 5:
					putimage(j*size, i*size, &image[5]);
					break;
				case 6:
					putimage(j*size, i*size, &image[6]);
					break;
				case 7:
					putimage(j*size, i*size, &image[7]);
					break;
				case 8:
					putimage(j*size, i*size, &image[8]);
					break;
				}
				break;
			}
		}
		//printf("\n");
	}
	EndBatchDraw();
}


void start()
{
	init();  //初始化游戏	
	draw();
	while (true)
	{
		play();  //游戏的操控
		draw();  //界面的绘制
		if (isGameOver)  //游戏失败
		{
			int a = MessageBox(GetForegroundWindow(), "是否继续游戏", "游戏结束", MB_YESNO);
			if (a == 6)  //表示按下了是
			{
				init_map();
			}
			else if (a == 7)
			{
				break;
			}


		}
	}
}

int main()
{

	start();
	return 0;
}

