#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h> //ͼ�ο�

//���콲̰������Ϸ

//8��׼ʱ�Ͽ�

#define MALLOC(type) (type*)malloc(sizeof(type));

//����ṹ��
struct Position
{
	int x;
	int y;
};

//�߽ڵ�
struct Snake
{
	Position pos;
	Snake *n;
};

enum Direction
{
	UP,		//��
	RIGHT,  //��
	DOWN,   //��
	LEFT	//��
};

enum GameMode
{
	death,
	infinite
};
GameMode mode;

Direction dir, recvDir;
int wid, hei; //��Ⱥ͸߶�
int size;
int maxX, maxY;

Snake *head = NULL;		//ͷ�ڵ�
Snake *tail = NULL;		//β�ڵ�

Position food;    //ʳ������

Snake* spawnNewBody()  //ctrl+r ctrl+r  �����ع�
{
	Snake *t = MALLOC(Snake);
	if (t == NULL)
	{
		printf("��Ϸ��ʼ��ʧ��:�ڴ治��\n");
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
	Snake *t = tail;
	while (t->n)
	{
		if (food.x == t->pos.x&&food.y == t->pos.y)
		{
			spawnNewFood();
			return;
		}
		t = t->n;
	}
}

bool isEatfood()
{
	if (head->pos.x == food.x&&head->pos.y == food.y)
	{
		return true;
	}
	return false;
}

bool isGameOver()
{
	Snake *t = tail;
	while (t != head&&t->n->n) //�����ж�ͷ�ڵ�
	{
		if (head->pos.x == t->pos.x&&head->pos.y == t->pos.y)
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


//��ʼ����Ϸ
void init_game()
{
	wid = 640; hei = 480;
	initgraph(wid, hei, SHOWCONSOLE);
	size = 20;
	maxX = wid / size;
	maxY = hei / size;
	tail = spawnNewBody();
	Snake *t = tail;
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
	int change = MessageBox(GetForegroundWindow(), _TEXT("ʹ������ģʽ?"), _TEXT("ѡ��ģʽ"), MB_YESNO);
	printf("\n\n%d\n\n", change);
	if (change==6)
		mode = death;
	else
		mode = infinite;

}

void snake_move()
{
	//β����ǰ�ƶ�
	Snake *t = tail;
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

//��Ϸ���ƺ���
void control()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (recvDir != DOWN)
		{
			dir = UP;
		}

	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (recvDir != LEFT)
		{
			dir = RIGHT;
		}
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (recvDir != UP)
		{
			dir = DOWN;
		}
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (recvDir != RIGHT)
		{
			dir = LEFT;
		}
	}
}


//��С����
void Rect(int x, int y, COLORREF color)
{
	setfillcolor(color);
	fillrectangle(x*size, y*size, x*size + size, y*size + size);
}

void draw()
{
	BeginBatchDraw(); //�������� ��ֹ��Ļ��������
	cleardevice();

	//�����߽ڵ�
	Snake *t = tail;
	while (t)
	{
		Rect(t->pos.x, t->pos.y, RGB(0xff, 0x66, 0x33));
		t = t->n;
	}
	//����ʳ��
	Rect(food.x, food.y, RGB(0x33, 0x66, 0xff));
	EndBatchDraw();//������������ ���˴˺���,ͼ�ν��޷����
}

//������Ϸ
void runGame()
{
	init_game();  //��ʼ����Ϸ
	spawnNewFood();//����ʳ��
	while (true)
	{
		//repeat
		snake_move();//���ƶ�
		control();//����
		if (isEatfood())
		{
			head->n = spawnNewBody();
			head = head->n;
			head->pos = food;
			spawnNewFood();
		}
		draw(); //���ƺ�����λ�÷�repeat��λ�� ��Ϸ�ָеı仯
		if (isGameOver())
		{
			MessageBox(GetForegroundWindow(), _TEXT("��Ϸ����"), _TEXT(""), 0);
			return;
		}
		Sleep(100); 
	}

}

//������
int main()
{
	runGame();
	return getchar();
}
