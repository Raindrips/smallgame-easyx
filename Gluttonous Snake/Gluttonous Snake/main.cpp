#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h> //图形库

#define MALLOC(type) ((type*)malloc(sizeof(type)));

//坐标结构体
struct Position
{
	int x;
	int y;
};

//蛇节点
struct Node
{
	Position pos;
	Node* n;
};

enum Direction
{
	UP,		//上
	RIGHT,  //右
	DOWN,   //下
	LEFT	//左
};

enum GameMode
{
	death,
	infinite
};
GameMode mode;

Direction dir, recvDir;
int wid, hei; //宽度和高度
int size;
int maxX, maxY;

Node* head = NULL;		//头节点
Node* tail = NULL;		//尾节点

Position food;    //食物坐标

Node* spawnNewBody()  //ctrl+r ctrl+r  代码重构
{
	Node* t = MALLOC(Node);
	if (t == NULL)
	{
		printf("游戏初始化失败:内存不足\n");
		getchar();
		exit(1);
	}
	t->pos = { -1, -1 };
	t->n = NULL;
	return t;
}


void spawnNewFood()
{
	food.x = rand() % maxX;
	food.y = rand() % maxY;
	Node* t = tail;
	while (t->n)
	{
		if (food.x == t->pos.x && food.y == t->pos.y)
		{
			spawnNewFood();
			return;
		}
		t = t->n;
	}
}

bool isEatfood()
{
	if (head->pos.x == food.x && head->pos.y == food.y)
	{
		return true;
	}
	return false;
}

bool isGameOver()
{
	Node* t = tail;
	while (t != head && t->n->n) //不会判断头节点
	{
		if (head->pos.x == t->pos.x && head->pos.y == t->pos.y)
		{
			return true;
		}
		t = t->n;
	}
	switch (mode) {
	case death:
		if (head->pos.x<0 || head->pos.x>maxX
			|| head->pos.y<0 || head->pos.y>maxY)
		{
			return true;
		}
		break;
	case infinite:
		if (head->pos.x < 0)
			head->pos.x = maxX - 1;
		if (head->pos.y < 0)
			head->pos.y = maxY - 1;

		if (head->pos.x >= maxX)
			head->pos.x = 0;
		if (head->pos.y >= maxY)
			head->pos.y = 0;
		break;
	}
	return false;
}


//初始化游戏
void init_game()
{
	wid = 640; hei = 480;
	initgraph(wid, hei);
	size = 20;
	maxX = wid / size;
	maxY = hei / size;
	tail = spawnNewBody();
	Node* t = tail;
	Position pos{ 5, 3 };
	for (int i = 0; i < 2; i++)
	{
		t->pos = pos;
		pos.x++;
		t->n = spawnNewBody();
		t = t->n;
	}
	t->pos = pos;
	head = t;
	srand(time(NULL));
	dir = RIGHT;
	int change = MessageBox(GetForegroundWindow(), _TEXT("使用生存模式?"), _TEXT("选择模式"), MB_YESNO);
	printf("\n\n%d\n\n", change);
	if (change == 6)
		mode = death;
	else
		mode = infinite;

}

void snake_move()
{
	//尾巴向前移动
	Node* t = tail;
	while (t->n)
	{
		t->pos = t->n->pos;
		t = t->n;
	}


	recvDir = dir;
	switch (dir)
	{
	case UP:
		head->pos.y--;
		break;
	case RIGHT:
		head->pos.x++;
		break;
	case DOWN:
		head->pos.y++;
		break;
	case LEFT:
		head->pos.x--;
		break;
	}
	printf("x:%d y:%d\n", head->pos.x, head->pos.y);

}

//游戏控制函数
void control()
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (recvDir != DOWN) {
			dir = UP;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (recvDir != LEFT) {
			dir = RIGHT;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (recvDir != UP) {
			dir = DOWN;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (recvDir != RIGHT) {
			dir = LEFT;
		}
	}
}


//画小方块
void Rect(int x, int y, COLORREF color)
{
	setfillcolor(color);
	fillrectangle(x * size, y * size, x * size + size, y * size + size);
}

void draw()
{
	BeginBatchDraw(); //批量绘制 防止屏幕出现闪动
	cleardevice();

	//绘制蛇节点
	Node* t = tail;
	while (t)
	{
		Rect(t->pos.x, t->pos.y, RGB(0xff, 0x66, 0x33));
		t = t->n;
	}
	//绘制食物
	Rect(food.x, food.y, RGB(0x33, 0x66, 0xff));
	EndBatchDraw();//结束批量绘制 少了此函数,图形将无法输出
}

//运行游戏
void runGame()
{
	init_game();  //初始化游戏
	spawnNewFood();//生成食物
	while (true)
	{
		control();//控制
		snake_move();//蛇移动
		if (isEatfood())
		{
			head->n = spawnNewBody();
			head = head->n;
			head->pos = food;
			spawnNewFood();
		}
		draw();
		if (isGameOver())
		{
			MessageBox(GetForegroundWindow(), _TEXT("游戏结束"), _TEXT(""), 0);
			return;
		}
		Sleep(100);
	}

}

//主函数
int main()
{
	runGame();
	return getchar();
}
