// 1.cpp : 定义控制台应用程序的入口点。
#include <easyx.h>
#include <list>
#include <ctime>
using std::list;

//坐标
struct Position
{
	int x;
	int y;
	Position(int x = 0, int y = 0) :x(x), y(y){}
};
//枚举类 方向
enum direction
{
	UP = 0,	//上
	RIGHT,	//右
	DOWN,	//下
	LEFT,	//左
};

//贪吃蛇
class Snake
{
private:
	list<Position> snake;  //蛇的身体
	direction dir_send,dir_recv;			//蛇移动的方向

	int wid, hei;
	int maxX, maxY;

	Position food;

	const int PIX = 20;	//方块的大小
	const int LEN = 9;  //蛇的初识长度
public:

	Snake(int wid = 480, int hei = 640) :wid(wid), hei(hei)
	{
		initgraph(wid, hei);
		maxX = wid / PIX;
		maxY = hei / PIX;
	}
	~Snake()
	{
		closegraph();
	}
	void start()
	{
		init();
		draw();
		while (true)
		{

			control();
			move();			
			draw();		//绘制函数在最后和放在最前面有什么区别
			if (isGameOver())
			{
				MessageBox(GetForegroundWindow(), +_T("游戏结束"), _T(""), MB_OK);
				getchar();
				break;
			}
			Sleep(100);
		}
	}

protected:
	//初始化游戏
	void init()
	{
		dir_send = DOWN;  //蛇默认移动的方向为下
		Position pos(5, 3);
		snake.push_front(pos);
		for (int i = 1; i < LEN; i++)
		{
			pos.x++;
			snake.push_front(pos);
		}

		spawnNewFood();
		srand(time(nullptr));  //生成随机数种子

	}
	void _rect(int x, int y)
	{
		fillrectangle(x*PIX, y*PIX, (x + 1)*PIX, (y + 1)*PIX);
	}

	void spawnNewFood()
	{
		food.x = rand() % maxX;
		food.y = rand() % maxY;
	}

	void move()
	{
		Position pos = snake.front();
		dir_recv = dir_send;
		switch (dir_recv)
		{
		case UP:
			pos.y--;
			break;
		case LEFT:
			pos.x--;
			break;
		case DOWN:
			pos.y++;
			break;
		case RIGHT:
			pos.x++;
			break;
		}
		if (pos.x < 0) pos.x = maxX - 1;
		if (pos.y < 0) pos.y = maxY - 1;
		if (pos.x >= maxX) pos.x = 0;
		if (pos.y >= maxY) pos.y = 0;

		if (isEatFood())
		{
			snake.push_front(pos);
			spawnNewFood();
		} else
		{
			snake.push_front(pos);
			snake.pop_back();
		}
	}

	void control()
	{
		if (GetAsyncKeyState(VK_UP) | GetAsyncKeyState('W'))
		{
			if (dir_recv != DOWN)
				dir_send = UP;
		}
		else if (GetAsyncKeyState(VK_RIGHT) | GetAsyncKeyState('D'))
		{
			if (dir_recv != LEFT)
				dir_send = RIGHT;
		}
		else if(GetAsyncKeyState(VK_DOWN) | GetAsyncKeyState('S'))
		{
			if (dir_recv != UP)
				dir_send = DOWN;
		}
		else if(GetAsyncKeyState(VK_LEFT) | GetAsyncKeyState('A'))
		{
			if (dir_recv != RIGHT)
				dir_send = LEFT;
		}
	}

	bool isEatFood()
	{
		return snake.front().x == food.x&&snake.front().y == food.y;
	}

	bool isGameOver()
	{
		for (auto p = ++snake.begin(); p != snake.end(); ++p)
		{
			if (p->x == snake.front().x&&p->y == snake.front().y)
			{
				return true;
			}
		}
		return false;
	}

	void draw()
	{
		BeginBatchDraw();
		cleardevice();
		setfillcolor(RGB(64, 192, 255));
		for (auto node : snake)
		{
			_rect(node.x, node.y);
		}
		setfillcolor(RGB(64, 255, 192));
		_rect(food.x, food.y);
		EndBatchDraw();
	}

};

int main()
{
	Snake snake(640, 480);
	snake.start();
	
	return 0;
}

