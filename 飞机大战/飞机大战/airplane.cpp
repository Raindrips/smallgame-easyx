#include "airplane.h"
#include "dlist.h"
#include <easyx.h>
#include <conio.h>

int wid = 360;		//��Ļ��� width
int hei = 600;		//��Ļ�߶� height

const int MAX_ENEMEY = 8;	//���ĵл�����
const int MAX_BULLET = 3;	//�����ӵ�����

IMAGE image[4];

enum jpg{ enemy = 0, plan, bullet, bg };

Node player = { 0, 0 };			//���
dlist* enemyplan;				//�л�
dlist* d_bullet;				//����������ӵ�


const int size = 40;			//�ɻ��Ĵ�С

int grade = 0;					//����
TCHAR score[30];				//��ʾ�������ַ���

//��ʼ����Ϸ,��ʼ��ͼ�ο�
void load()
{
	initgraph(wid, hei);
	loadimage(&image[enemy], _T("res/1.jpg"), size, size);
	loadimage(&image[plan], _T("res/2.jpg"), size, size);
	loadimage(&image[bullet], _T("res/3.jpg"));
	loadimage(&image[bg], _T("res/4.jpg"), wid, hei);
}

//��ʼ������
void init()
{
	//��ҷɻ��ĳ�ʼλ��  ���/2 ���λ�����м�
	player = { (wid - size) / 2, hei - size * 2 };
	enemyplan = dlist_init();	//�л�����ĳ�ʼ��
	d_bullet = dlist_init();	//�ӵ�����ĳ�ʼ��
	grade = 0;					//����
}

//��ʼ��Ϸ
void start()
{
	load();
	init();
	while (true)
	{
		control();	
		update();
		draw();
		if (isGameOver())
		{
			TCHAR tc[512] = {};
			wsprintf(tc, _T("��ǰ�÷�:%d \n�Ƿ����¿�ʼ��Ϸ?"), grade);
			if (MessageBox(GetForegroundWindow(), tc, _T("��Ϸ����"), MB_YESNO) == IDYES)
			{
				//�ͷ������е��ڴ�
				dlist_clear(d_bullet);
				dlist_clear(enemyplan);
				init();		//��ʼ��
			}
			else
			{
				break;
			}
		}
		Sleep(16);  //ÿ��ѭ���������ߵ�ʱ��
	}
}

//��������
void update()
{
	//�������зɻ�
	for (Node* t = enemyplan->front; t != NULL; t = t->next)
	{
		t->y += 2;		//�ɻ������ƶ�2����
	}
	//���������ӵ��ڵ�
	for (Node* t = d_bullet->front; t != NULL; t = t->next)
	{
		t->y -= 8;		//�ӵ������ƶ�
	}
	spawnEnemy();
	destroy();
	bulletCollide();
}

//���ƻ���
void draw()
{
	BeginBatchDraw();
	putimage(0, 0, &image[bg]);//���Ʊ���
	//�����ɻ��ڵ�
	for (Node* t = enemyplan->front; t != NULL; t = t->next)
	{
		//���Ʒɻ�
		putimage(t->x, t->y, &image[enemy]);
	}
	//�����ӵ��ڵ�
	for (Node* t = d_bullet->front; t != NULL; t = t->next)
	{
		putimage(t->x, t->y, &image[bullet]);//�����ӵ�
	}
	putimage(player.x, player.y, &image[plan]);//������ҵķɻ�


	wsprintf(score, _T("score:%d"), grade);
	settextcolor(0);						//����������ɫ
	setbkmode(TRANSPARENT);					//��������͸��
	outtextxy(wid / 2 - 20, size, score);		//����Ļ�ϻ�������

	EndBatchDraw();
}

//��Ϸ����
void control()
{
	int speed = 5;
	if (GetAsyncKeyState(SHIFT_PRESSED))
	{
		speed = 3;
	}
	//scanf getch _kbhit ������
	//��GetAsynKeyState   ��ȡ���̰���   <windows.h>
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (player.y > 0)
		{
			player.y -= speed;
		}
	}if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y < hei - size)
		{
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x > 0)
		{
			player.x -= speed;
		}
	}if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x < wid - size)
		{
			player.x += speed;
		}
	}
	//�����ӵ�ֻҪ�ж�һ�ΰ��¾���
	if (_kbhit())		//�жϰ�����Ϣ,����һ������
	{
		int key = _getch();
		if (key == ' ')
		{
			spawnBullet();
		}
	}
}

//�ж���Ϸ�Ƿ����
bool isGameOver()
{
	for (Node* n = enemyplan->front; n != NULL; n = n->next)
	{
		if (planeCollide(&player, n))
		{
			return true;
		}
	}
	return false;
}


//���ɵл�
void spawnEnemy()
{
	static int count = 0;  //ʹ�������ֻ��ʼ��һ��,�ڶ��λ�����������

	if (count >= 30)  //�л����ɵ�����
	{
		//MAX_ENEMEY�л�������ɵ�����
		if (dlist_size(enemyplan) < MAX_ENEMEY)
		{
			dlist_push(enemyplan, node_init(rand() % (wid - size), 0));
		}
		count = 0;
	}
	count++;
}


void spawnBullet()
{
	if (dlist_size(d_bullet) < MAX_BULLET)
	{
		//����ӵ��ڵ�,�ڷɻ�������λ��
		dlist_push(d_bullet, node_init(player.x + size / 2 - 4, player.y));
	}
}


void destroy()
{
	//����ӵ�,�ӵ�������Ļ��,�ͻᱻ����
	for (Node *n = d_bullet->front; n != NULL; n = n->next)
	{
		if (n->y < 0)  //����С��0,˵���Ѿ��Ƴ���Ļ��
		{
			dlist_pop(d_bullet, n);
			grade = grade - 5 > 0 ? grade - 5 : 0;
			break;	//����n������,�޷�����ѭ��������ȥ,��������ѭ��
		}
	}

	//����ɻ�
	for (Node *n = enemyplan->front; n != NULL; n = n->next)
	{
		if (n->y > hei)	//�ɻ��Ƴ�����Ļ��
		{
			dlist_pop(enemyplan, n);//���ٸ÷ɻ�
			break;
		}
	}
}

//�ӵ���ײ,��������л�,������
void bulletCollide()
{
	//ѭ�������ӵ�����ڵ�
	for (Node* b = d_bullet->front; b != NULL; b = b->next)
	{
		//ѭ�������л�������ڵ�
		for (Node* en = enemyplan->front; en != NULL; en = en->next)
		{
			//�ӵ�ײ���˷ɻ�
			if (planeCollide(b, en))
			{
				//�Ƴ��ӵ��ͷɻ�
				dlist_pop(d_bullet, b);
				dlist_pop(enemyplan, en);
				grade++;//����+1
				return;
			}
		}
	}
}


bool planeCollide(const Node *n1, const Node *n2)
{
	int x = abs(n1->x - n2->x);
	int y = abs(n1->y - n2->y);
	return x < size && y < size;
}
