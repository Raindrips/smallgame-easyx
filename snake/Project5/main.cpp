#include <stdio.h>
#include <easyx.h>
#include <time.h>

//����
struct Position
{
  int x;
  int y;
};

//�߽ڵ�
struct Snake
{
  Position pos;
  Snake* next;
};

//���ƶ��ķ���
enum Direction
{
  UP,		//��
  RIGHT,	//��
  DOWN,	//��
  LEFT	//��
};
Direction dir;

int wid = 600, hei = 600;	//ͼ��Ŀ�Ⱥ͸߶�
int px = 20;			//ÿ����������ش�С
int mx, my;				//��������ֵ

Snake* head = NULL;		//�ߵ�ͷ��
Snake* tail = NULL;		//�ߵ�β��

Position food;


Snake* spawnNewBody()
{
  Snake* temp = (Snake*)malloc(sizeof(Snake));
  if (temp == NULL)
  {
	printf("�����ڴ�ʧ��:%d\n", __LINE__);
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

//��ʼ����Ϸ
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

//���ƶ�
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

//��Ϸ���ƺ���
void control()
{
  //�Ϸ��򽨰���
  if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	&& dir != DOWN)
  {
	dir = UP;
  }
  //�ҷ��򽨰���
  else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	&& dir != LEFT)
  {
	dir = RIGHT;
  }
  //�·��򽨰���
  else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	&& dir != UP)
  {
	dir = DOWN;
  }
  //���򽨰���
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
  //�Ƿ�ײ��ǽ
  Snake* t = tail;
  if (head->pos.x >= mx || head->pos.y >= my || head->pos.x < 0 || head->pos.y < 0)
  {
	return true;
  }
  //�Ƿ��Ե��Լ�
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

//������Ϸ
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
