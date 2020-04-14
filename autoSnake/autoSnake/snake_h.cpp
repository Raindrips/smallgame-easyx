#include "snake_h.h"

int Snake::snake_bsize()
{
	return snake_b.size();
}


//template<class Position>
bool Snake::findtail(deque<Position>path, A_strak strak)
{
	deque<Position>de(path.begin(), path.end());
	Pos _snake_h=snake_h;//蛇头
	Pos _food=food;//食物坐标
	Pos _tail=tail;//蛇尾坐标
	deque<Pos*>_snake_b(snake_b.begin(),snake_b.end());//蛇身
	vector<vector<int>>_game_map(game_map.begin(),game_map.end());//地图
	de.pop_front();
	for (auto pox : de)
	{
		mobile_s(pox.x, pox.y);
		//if (pos.x == s.gets_x()&&pos.y==s.gets_y())
		if (food.x==snake_h.x&&food.y==snake_h.y)
		{
			break;
		}
	}
	de.clear();
	if (strak.findPath(snake_h.x, snake_h.y, tail.x, tail.y, de))
	{
		snake_h = _snake_h;//蛇头
		food = _food;//食物坐标
		tail = _tail;//蛇尾坐标
		snake_b.assign(_snake_b.begin(), _snake_b.end());//蛇身
		game_map.assign(_game_map.begin(), _game_map.end());//地图
		return true;
	}
	else
	{
		snake_h = _snake_h;//蛇头
		food = _food;//食物坐标
		tail = _tail;//蛇尾坐标
		snake_b.assign(_snake_b.begin(), _snake_b.end());//蛇身
		game_map.assign(_game_map.begin(), _game_map.end());//地图
		return false;
	}
}
int Snake::gett_x()
{
	return tail.x;
}

int Snake::gett_y()
{
	return tail.y;
}
Snake::Snake(int map_x, int map_y, vector<vector<int>>game_map) :map_x(map_x), map_y(map_y), game_map(game_map)
{
	initgraph(this->map_x, this->map_y, SHOWCONSOLE);
	size = this->map_x / game_map.size();
	_null = true;
	inArea = [=](int x, int y)
	{
		if (x < 0 || y < 0 || x >= this->game_map.size() || y >= this->game_map.size())
		{
			return false;
		}
		if (this->game_map[y][x] == 2 || this->game_map[y][x] == 1)
		{
			return false;
		}
		return true;
	};
}

int Snake::getsize()
{
	return 30;
}

void Snake::initfood()
{
	srand((unsigned)time(NULL));
	do
	{
		food.x = rand() % game_map.size();
		food.y = rand() % game_map.size();
	} while (game_map[food.y][food.x] != 0);
	game_map[food.y][food.x] = 3;
}

Pos Snake::getfood()
{
	return food;
}

Pos Snake::getsnake_h()
{
	return snake_h;
}

int Snake::gets_x()
{
	return snake_h.x;
}

int Snake::gets_y()
{
	return snake_h.y;
}

int Snake::getf_x()
{
	return food.x;
}

int Snake::getf_y()
{
	return food.y;
}

vector<vector<int>> Snake::gedgame_map()
{
	return game_map;
}

void Snake::getsnake()
{
	snake_h.x = 1;
	snake_h.y = 20;
	game_map[snake_h.y][snake_h.x] = 1;
}

void Snake::mobile_s(int x, int y)
{
	if (_null)
	{
		game_map[y][x] = 1;
		if (x == food.x&&y == food.y)
		{
			snake_b.push_back(new Pos(snake_h.x, snake_h.y));
			game_map[snake_h.y][snake_h.x] = 4;
			_null = false;
		}
		else
		{
			game_map[snake_h.y][snake_h.x] = 0;
		}
		snake_h.x = x;
		snake_h.y = y;
		if (snake_b.size() != 0)
		{
			auto i = snake_b.back();
			tail.x = i->x;
			tail.y = i->y;
		}
	}
	else
	{
		if (x != food.x || y != food.y)
		{
			auto i = snake_b.back();
			game_map[i->y][i->x] = 0;
			snake_b.pop_back();
		}
		game_map[y][x] = 1;
		game_map[snake_h.y][snake_h.x] = 2;
		snake_b.push_front(new Pos(snake_h.x, snake_h.y));
		snake_h.x = x;
		snake_h.y = y;
		auto j = snake_b.back();
		game_map[j->y][j->x] = 4;
		tail.x = j->x;
		tail.y = j->y;
	}
}

void Snake::init()
{
	BeginBatchDraw();
	for (int i = 0; i < game_map.size(); i++)
	{
		for (int j = 0; j < game_map[i].size(); j++)
		{
			switch (game_map[i][j])
			{
			case 1:
				setfillcolor(RGB(0, 245, 255));
				solidrectangle(j*size + 1, i * size + 1, (j + 1) * size - 1, (i + 1) * size - 1);
				break;
			case 2:
				setfillcolor(RED);
				fillrectangle(j * size + 1, i * size + 1, (j + 1) * size - 1, (i + 1)*size - 1);
				break;
			case 3:
				setfillcolor(RGB(255, 106, 106));
				solidcircle(j*size + size / 2, i * size + size / 2, size / 2);
				break;
			case 4:
				setfillcolor(WHITE);
				fillrectangle(j * size + 1, i * size + 1, (j + 1) * size - 1, (i + 1)*size - 1);
				break;
			}
		}
	}
	EndBatchDraw();

}

Snake::~Snake()
{
	for (auto i : snake_b)
	{
		delete i;
		i = nullptr;
	}
	//closegraph();
}
Pos::Pos(int x, int y) :x(x), y(y)
{

}

Pos::Pos()
{

}
