// 别踩白块.cpp : 定义控制台应用程序的入口点。
//8:00上课
#include <stdio.h>
#include <easyx.h>  
#include <stdlib.h>
#include <time.h>

int pxW = 100;//矩形宽度
int pxH = 150;//矩形高度
int block = 4;//块的数量

int black[4] = { 0 };
int count = 0;  //统计
bool is_init = false;

//初始化游戏
void game_init()
{
	if (!is_init)
		initgraph(pxW * block, pxH * block, SHOWCONSOLE);

	is_init = true;
	srand(time(NULL));
	for (int i = 0; i < block; i++)
	{
		black[i] = rand() % 4;
	}
	setbkcolor(RGB(255, 255, 255));
	count = 0;
}

//游戏控制
void game_control()
{
	MOUSEMSG msg = GetMouseMsg();  //获取鼠标信息
	if (msg.uMsg == WM_LBUTTONDOWN)  //获取鼠标按下信息 
	{
		int x = msg.x / pxW; //点击的x坐标
		int y = msg.y / pxH;//点击的y坐标
		printf("(%d,%d)\n", x, y);
		if (3 == y && x == black[3])
		{
			for (int i = 3; i > 0; i--)
			{
				black[i] = black[i - 1];
			}
			black[0] = rand() % 4;
			count++;
		}
		else if (3 == y) //游戏结束
		{
			MessageBox(GetForegroundWindow(), _TEXT("游戏结束"), _TEXT(""), 0);
			game_init();
		}
	}
}

//绘制背景
void drawbK()
{
	cleardevice();
	setlinecolor(RGB(36, 36, 36));
	/*
	//循环遍历,绘制白色虚线
	for (int i = 0; i < block; i++)
	{
	for (int j = 0; j < block; j++)
	{
	rectangle(j*pxW, i*pxH, (j + 1)*pxW, (i + 1)*pxH);
	}
	}
	*/

	//绘制虚线
	for (int i = 1; i < block; i++)
	{
		line(pxW * i, 0, pxW * i, pxH * block);
		line(0, pxH * i, pxW * block, pxH * i);
	}

}

//绘制黑块
void drawBlack()
{
	setfillcolor(0x0);
	for (int i = 0; i < block; i++)
	{
		fillrectangle(black[i] * pxW, i * pxH, (black[i] + 1) * pxW, (i + 1) * pxH);
	}
}

void drawText()
{
	setbkmode(TRANSPARENT);//指定图案填充和文字输出时的背景模式 设置为透明背景
	settextstyle(30, 20, _T("黑体"));
	RECT rect = { 0, 0, pxW * 4, pxH };
	settextcolor(0x6699ff);
	TCHAR t[1000];
	wsprintf(t, "%d", count);
	drawtext(t, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
}

//游戏绘制
void game_draw()
{
	BeginBatchDraw();
	drawbK();
	drawBlack();
	drawText();
	EndBatchDraw();
}

//游戏运行
void game_run()
{
	game_init();
	while (true)
	{
		game_control();
		game_draw();
	}
}

int main()
{
	game_run();
	return 0;
}

