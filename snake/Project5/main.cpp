#include <stdio.h>
#include <easyx.h>
#include <time.h>

//坐标
struct Position
{
  int x;
  int y;
};

//蛇节点
struct Snake
{
  Position pos;
  Snake* next;
};

//蛇移动的方向
enum Direction
{
  UP,		//上
  RIGHT,	//右
  DOWN,	//下
  LEFT	//左
};
Direction dir;

int wid = 600, hei = 600;	//图像的宽度和高度
int px = 20;			//每个方块的显素大小
int mx, my;				//坐标的最大值

Snake* head = NULL;		//蛇的头部
Snake* tail = NULL;		//蛇的尾部

Position food;


Snake* spawnNewBody()
{
  Snake* temp = (Snake*)malloc(sizeof(Snake));
  if (temp == NULL)
  {
	printf("申请内存失败:%d\n", __LINE__);
	return NULL;
  }
  temp->next = NULL;
  return temp;
}

void spawnNewFood()
{
  Snake* t = tail;
  food.x = rand() % mx;
  food.y = rand() % my;
  while (t->next)
  {
	if (t->pos.x == food.x && t->pos.y == food.y)
	{
	  spawnNewFood();
	  return;
	}
	t = t->next;
  }

}

//初始化游戏
void init()
{
  initgraph(wid, hei);
  mx = wid / px;
  my = hei / px;
  dir = DOWN;
  Position pos = { 5, 3 };
  tail = spawnNewBody();
  Snake* t = tail;
  for (int i = 0; i < 2; i++)
  {
	t->pos = pos;
	pos.x++;
	t->next = spawnNewBody();
	t = t->next;
  }
  t->pos = pos;
  head = t;
  srand(time(NULL));
}

//蛇移动
void move()
{
  Snake* t = tail;
  while (t->next)
  {
	t->pos = t->next->pos;
	t = t->next;
  }
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
}

//游戏控制函数
void control()
{
  //上方向建按下
  if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	&& dir != DOWN)
  {
	dir = UP;
  }
  //右方向建按下
  else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	&& dir != LEFT)
  {
	dir = RIGHT;
  }
  //下方向建按下
  else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	&& dir != UP)
  {
	dir = DOWN;
  }
  //左方向建按下
  else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	&& dir != RIGHT)
  {
	dir = LEFT;
  }
}

void fillRect(int x, int y, COLORREF color)
{
  setfillcolor(color);
  fillrectangle(x * px, y * px, x * px + px, y * px + px);
}

bool isEatFood()
{
  if (head->pos.x == food.x && head->pos.y == food.y)
  {
	return true;
  }
  return false;
}

bool isGmaeover()
{
  //是否撞到墙
  Snake* t = tail;
  if (head->pos.x >= mx || head->pos.y >= my || head->pos.x < 0 || head->pos.y < 0)
  {
	return true;
  }
  //是否会吃到自己
  while (t->next->next)
  {
	if (t != head && t->pos.x == head->pos.x && head->pos.y == t->pos.y)
	{
	  return true;
	}
	t = t->next;
  }
  
  return false;
}

void draw()
{

  Snake* t = tail;
  cleardevice();
  while (t)
  {
	fillRect(t->pos.x, t->pos.y, 0x3366ff);
	t = t->next;
  }
  fillRect(food.x, food.y, 0xff3366);
}

//运行游戏
void runGame()
{
  init();
  spawnNewFood();
  while (true)
  {

	control();
	move();
	if (isEatFood())
	{
	  head->next = spawnNewBody();
	  head = head->next;
	  head->pos = food;
	  spawnNewFood();
	}
	if (isGmaeover())
	{
	  MessageBox(GetForegroundWindow(), TEXT("GAME OVER"), NULL, 0);
	  return;
	}
	draw();
	Sleep(100);
  }
}

int main(int argc, char* argv[])
{
  runGame();
}
