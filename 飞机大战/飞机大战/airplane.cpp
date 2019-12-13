#include "airplane.h"
#include "dlist.h"
#include <easyx.h>
#include <conio.h>

int wid = 360;		//屏幕宽度 width
int hei = 600;		//屏幕高度 height

const int MAX_ENEMEY = 8;	//最大的敌机数量
const int MAX_BULLET = 3;	//最大的子弹数量

IMAGE image[4];

enum jpg{ enemy = 0, plan, bullet, bg };

Node player = { 0, 0 };			//玩家
dlist* enemyplan;				//敌机
dlist* d_bullet;				//发射出来的子弹


const int size = 40;			//飞机的大小

int grade = 0;					//分数
TCHAR score[30];				//显示分数的字符串

//初始化游戏,初始化图形库
void load()
{
	initgraph(wid, hei);
	loadimage(&image[enemy], _T("res/1.jpg"), size, size);
	loadimage(&image[plan], _T("res/2.jpg"), size, size);
	loadimage(&image[bullet], _T("res/3.jpg"));
	loadimage(&image[bg], _T("res/4.jpg"), wid, hei);
}

//初始化数据
void init()
{
	//玩家飞机的初始位置  宽度/2 玩家位置在中间
	player = { (wid - size) / 2, hei - size * 2 };
	enemyplan = dlist_init();	//敌机链表的初始化
	d_bullet = dlist_init();	//子弹链表的初始化
	grade = 0;					//分数
}

//开始游戏
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
			wsprintf(tc, _T("当前得分:%d \n是否重新开始游戏?"), grade);
			if (MessageBox(GetForegroundWindow(), tc, _T("游戏结束"), MB_YESNO) == IDYES)
			{
				//释放链表中的内存
				dlist_clear(d_bullet);
				dlist_clear(enemyplan);
				init();		//初始化
			}
			else
			{
				break;
			}
		}
		Sleep(16);  //每次循环调用休眠的时间
	}
}

//更新数据
void update()
{
	//遍历所有飞机
	for (Node* t = enemyplan->front; t != NULL; t = t->next)
	{
		t->y += 2;		//飞机向下移动2像素
	}
	//遍历所有子弹节点
	for (Node* t = d_bullet->front; t != NULL; t = t->next)
	{
		t->y -= 8;		//子弹向上移动
	}
	spawnEnemy();
	destroy();
	bulletCollide();
}

//绘制画面
void draw()
{
	BeginBatchDraw();
	putimage(0, 0, &image[bg]);//绘制背景
	//遍历飞机节点
	for (Node* t = enemyplan->front; t != NULL; t = t->next)
	{
		//绘制飞机
		putimage(t->x, t->y, &image[enemy]);
	}
	//遍历子弹节点
	for (Node* t = d_bullet->front; t != NULL; t = t->next)
	{
		putimage(t->x, t->y, &image[bullet]);//绘制子弹
	}
	putimage(player.x, player.y, &image[plan]);//绘制玩家的飞机


	wsprintf(score, _T("score:%d"), grade);
	settextcolor(0);						//设置文字颜色
	setbkmode(TRANSPARENT);					//设置文字透明
	outtextxy(wid / 2 - 20, size, score);		//在屏幕上绘制文字

	EndBatchDraw();
}

//游戏控制
void control()
{
	int speed = 5;
	if (GetAsyncKeyState(SHIFT_PRESSED))
	{
		speed = 3;
	}
	//scanf getch _kbhit 都不行
	//用GetAsynKeyState   获取键盘按下   <windows.h>
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
	//发射子弹只要判断一次按下就行
	if (_kbhit())		//判断按键消息,按下一个键就
	{
		int key = _getch();
		if (key == ' ')
		{
			spawnBullet();
		}
	}
}

//判断游戏是否结束
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


//生成敌机
void spawnEnemy()
{
	static int count = 0;  //使这个变量只初始化一次,第二次会跳过该声明

	if (count >= 30)  //敌机生成的周期
	{
		//MAX_ENEMEY敌机最大生成的数量
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
		//添加子弹节点,在飞机的中心位置
		dlist_push(d_bullet, node_init(player.x + size / 2 - 4, player.y));
	}
}


void destroy()
{
	//清除子弹,子弹超出屏幕外,就会被销毁
	for (Node *n = d_bullet->front; n != NULL; n = n->next)
	{
		if (n->y < 0)  //坐标小于0,说明已经移出屏幕了
		{
			dlist_pop(d_bullet, n);
			grade = grade - 5 > 0 ? grade - 5 : 0;
			break;	//由于n被销毁,无法继续循环遍历下去,所有跳出循环
		}
	}

	//清除飞机
	for (Node *n = enemyplan->front; n != NULL; n = n->next)
	{
		if (n->y > hei)	//飞机移出了屏幕外
		{
			dlist_pop(enemyplan, n);//销毁该飞机
			break;
		}
	}
}

//子弹碰撞,如果碰到敌机,就销毁
void bulletCollide()
{
	//循环遍历子弹链表节点
	for (Node* b = d_bullet->front; b != NULL; b = b->next)
	{
		//循环遍历敌机的链表节点
		for (Node* en = enemyplan->front; en != NULL; en = en->next)
		{
			//子弹撞到了飞机
			if (planeCollide(b, en))
			{
				//移除子弹和飞机
				dlist_pop(d_bullet, b);
				dlist_pop(enemyplan, en);
				grade++;//分数+1
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
