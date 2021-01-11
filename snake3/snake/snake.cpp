#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <easyx.h>//图形库头文件
#include<Windows.h>//windows系统库
struct Position//坐标
{
	int x;//x轴
	int y;//y轴
};

struct Snake//蛇的节点
{
	 Position pos;//方向
	 Snake *next;//指向下一个节点
};

enum direction//蛇的移动方向上下左右
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

direction dir;//蛇移动的方向
Position food;//食物的节点



struct Snake* spawnNewbody()//蛇的节点
{
	 Snake* temp = (Snake*)malloc(sizeof(Snake));//申请内存
	if (temp == NULL)
	{
		printf("申请内存失败:%d\n", __LINE__);//找到bug的行数
	}
	temp->next = NULL;
	return temp;
}

 Snake *head = NULL;//蛇的头部//给指针初始化为空
 Snake *tail = NULL;//蛇的尾部

int wid = 400, hei = 400;//宽高
int px = 20;//像素大小，表示蛇和食物的大小
int mx, my;//方块坐标的最大值

void spawnNewfood()//生成食物
{
	food.x = rand() % mx;
	food.y = rand() % my;
	Snake *t=tail;
	while (t->next)
	{
		if (food.x == t->pos.x&&food.y == t->pos.y)
		{
			spawnNewfood();
			break;
		}
		t = t->next;
	}
}

bool iseatfood()//检测是否吃到食物
{
	if (head->pos.x == food.x&&food.y == head->pos.y)
	{
		return true;
	}
	return false;
}
void init()//初始化游戏的函数
{
	initgraph(400, 400);
	mx = wid / px;
	my = hei / px;
	Position pos = { 5, 3 };
	tail = spawnNewbody();//创建蛇新的身体在链表尾部
	Snake* h = tail;//临时变量保存head
	for (int i = 0; i < 2; i++)//遍历身体节点
	{
		h->pos = pos;//让head的坐标为我们给的{5，3}
		pos.x++;
		h->next = spawnNewbody();//给身体新建第二个节点
		h = h->next;
	}
	h->pos = pos;//单链表
	head = h;
	dir = DOWN;
	srand(time(NULL));//初始化随机种子
}

void move()//蛇的移动
{
	Snake*t = tail;//尾节点临时变量
	Snake *h = head;//头节点使用临时变量
	while (t->next != NULL)//让尾部跟着头部动
	{
		t->pos = t->next->pos;//尾巴的坐标=头部的坐标
		t = t->next;
	}
	switch (dir)//判断方向，坐标变化
	{
	case UP:
		h->pos.y--;
		break;
	case DOWN:
		h->pos.y++;
		break;
	case RIGHT:
		h->pos.x++;
		break;
	case LEFT:
		h->pos.x--;
		break;
	}
}

void drawpix(int x,int y,COLORREF color)//绘制一个方块,xy坐标和绘制的颜色
{
	setfillcolor(color);//设置填充颜色
	//用指定的图象填充坐标在(x, y)处，宽width，高height的矩形
	fillrectangle(x*px, y*px, x*px + 20, y*px + 20);
}

void draw()//图形的绘制
{  //遍历节点绘制方块
	cleardevice();//清除图形屏幕
	Snake *t = tail;//尾节点临时变量
	while (t)
	{
		drawpix(t->pos.x,t->pos.y,0x366ff);
		t = t->next;
	}
	drawpix(food.x, food.y, 0xff12);
}


void changeDir()//改变蛇运行方向的函数
{
	//检测键盘按下的键
	if (GetAsyncKeyState(VK_UP))
	{
		if (dir!=DOWN)
		dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (dir != UP)
		dir = DOWN;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (dir != LEFT)
		dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (dir != RIGHT)
		dir = LEFT;
	}
}

bool isGameover()//判断游戏是否结束
{
	//判断是否会吃到自己
	Snake*t = tail;
	if (t != head&&t->next)
	{
		if (t->pos.x == head->pos.x&&t->pos.y == head->pos.y)
		{
			return true;
		}
	}
	//是否撞到墙
	if (head->pos.x<0 || head->pos.x>mx || head->pos.y<0 || head->pos.y>my)
	{
		return true;
	}
	return false;
}

void rungame()//运行游戏的函数
{
	init();
	spawnNewfood();
	while (true)
	{
		move();
		changeDir();
		if (iseatfood())
		{
			head->next = spawnNewbody();
			head = head->next;
			head->pos = food;
			spawnNewfood();
		}
		if (isGameover())
		{
			//显示对话框
			MessageBox(GetForegroundWindow(), TEXT("GAME OVER"), NULL, 0);
			break;
		}
		draw();
		Sleep(200);
	}
}

int main()
{

	rungame();

	return 0;
}