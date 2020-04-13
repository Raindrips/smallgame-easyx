// 别踩白块.cpp : 定义控制台应用程序的入口点。
//8:00上课
#include <stdio.h>
#include <easyx.h>  
#include <stdlib.h>
#include <time.h>

#include <conio.h>

//游戏模式
enum mode
{
	MOUSE,
	KEYBOARD,
};


int pxW = 100;//矩形宽度
int pxH = 150;//矩形高度
int block = 4;//块的数量

int black[4] = { 0 };
int count = 0;  //统计
bool is_init = false;
mode m = MOUSE;
clock_t start;
clock_t end;

struct Pos
{
	int x;
	int y;
};
Pos rect[4][4];

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
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < block; j++)
		{
			rect[i][j] = { j*pxW, i*pxH };
		}
	}
	setbkcolor(RGB(255, 255, 255));
	count = 0;
	start = time(NULL);
}

void GameOver()
{
	TCHAR tc[1000] = { 0 };
	wsprintf(tc, "你获得了 %d 分\n", count);
	MessageBox(GetForegroundWindow(), tc, _TEXT("游戏结束"), 0);
	game_init();
}

//游戏控制
void game_mouse()
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
			GameOver(); 
		}
	}
}

void game_keyboard()
{
	int key = -1;
	if (_kbhit())
	{

		char ch = _getch();
		if (ch == 'a' || ch == 'A')
		{
			key = 0;
		}
		else if (ch == 's' || ch == 'S')
		{
			key = 1;
		}
		else if (ch == 'j' || ch == 'J')
		{
			key = 2;
		}
		else if (ch == 'k' || ch == 'K')
		{
			key = 3;
		}

	}
	if (key == black[3])
	{
		for (int i = 3; i > 0; i--)
		{
			black[i] = black[i - 1];
		}
		black[0] = rand() % 4;
		count++;
	}
	else if (key != -1 && key != black[3]) //游戏结束
	{
		GameOver();
	}

}

//绘制背景
void drawbK()
{
	cleardevice();
	
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < block; j++)
		{
			if (black[i] == j)
			{
				//绘制黑块
				setlinecolor(0xffffff);
				setfillcolor(0x0);
			}
			else
			{
				//绘制白块
				setlinecolor(0x0);
				setfillcolor(0xeeeeee);
			}
			fillrectangle(rect[i][j].x, rect[i][j].y, rect[i][j].x + pxW, rect[i][j].y + pxH);
		}

	}
}

void drawText()
{
	setbkmode(TRANSPARENT);//指定图案填充和文字输出时的背景模式 设置为透明背景
	settextstyle(30, 20, _T("黑体"));
	RECT rect = { 0, 0, pxW * 4, pxH };
	settextcolor(0x6699ff);
	TCHAR t[1000];
	wsprintf(t, "%d %ds", count,60-(int)difftime(end,start));
	drawtext(t, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);


}

//游戏绘制
void game_draw()
{
	BeginBatchDraw();
	drawbK();
	drawText();
	EndBatchDraw();
}

void game_updata()
{
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < block; j++)
		{
			rect[i][j].y += 2;
		}
	}
}

//游戏运行
void game_run()
{
	game_init();
	game_draw();
	
	while (true)
	{
		if (m==KEYBOARD)
		{
			game_keyboard();   //用键盘
		} else if (m == MOUSE)
		{
			game_mouse();		//用鼠标  d f  j k
		}
		game_draw();
		Sleep(1);
		end = time(NULL);
		double t=difftime(end, start);
		if (t>=60)
		{
			MessageBox(GetForegroundWindow(), _TEXT("时间到"), _TEXT(""), 0);
			GameOver();
		}
		//printf("%lf\n", t);
	}
}

int main()
{
	game_run();
	return 0;
}

