#include "SnakeModule.h"
#include <easyx.h>
 Snake::Snake(int wid, int hei) :wid(wid), hei(hei)
{
	initgraph(wid, hei);
	maxX = wid / PIX;
	maxY = hei / PIX;
}

 Snake::~Snake()
{
	closegraph();
}

 void Snake::start()
{
	init();
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

//初始化游戏

 void Snake::init()
{
	dir_send = direction::DOWN;  //蛇默认移动的方向为下
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

 void Snake::_rect(int x, int y)
{
	fillrectangle(x * PIX, y * PIX, (x + 1) * PIX, (y + 1) * PIX);
}

 void Snake::spawnNewFood()
{
	food.x = rand() % maxX;
	food.y = rand() % maxY;
}

 void Snake::move()
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
	}
	else
	{
		snake.push_front(pos);
		snake.pop_back();
	}
}

 void Snake::control()
{
	if (GetAsyncKeyState(VK_UP) | GetAsyncKeyState('W'))
	{
		if (dir_recv != direction::DOWN)
			dir_send = direction::UP;
	}
	else if (GetAsyncKeyState(VK_RIGHT) | GetAsyncKeyState('D'))
	{
		if (dir_recv != direction::LEFT)
			dir_send = direction::RIGHT;
	}
	else if (GetAsyncKeyState(VK_DOWN) | GetAsyncKeyState('S'))
	{
		if (dir_recv != direction::UP)
			dir_send = direction::DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) | GetAsyncKeyState('A'))
	{
		if (dir_recv != direction::RIGHT)
			dir_send = direction::LEFT;
	}
}

 bool Snake::isEatFood()
{
	return snake.front().x == food.x && snake.front().y == food.y;
}

 bool Snake::isGameOver()
{
	for (auto p = ++snake.begin(); p != snake.end(); ++p)
	{
		if (p->x == snake.front().x && p->y == snake.front().y)
		{
			return true;
		}
	}
	return false;
}

 void Snake::draw()
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
