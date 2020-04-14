#include "DFS.h"


bool DFS::legal(int x, int y)
{
	for (auto i : path)
	{
		if (x == i.x&&y == i.y)
		{
			return false;
		}
	}
	return true;
}

DFS::DFS(function<bool(int, int)> inArea) :inArea(inArea)
{
}

void DFS::find(int x, int y, Pos &food, function<bool(int, int)> inArea)
{
	this->inArea = inArea;
	gameover = false;
	path.push_back(Pos(x, y));
	//std::cout << searcheat(x, y, food);
	if (searcheat(x, y, food))
	{
		searcheat(x, y, food);
	}
	else
		return;
}

bool DFS::searcheat(int x, int y, Pos &food)
{
	int dir[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	for (int i = 0; i < 4; i++)
	{
		int dx = x + dir[i][1];
		int dy = y + dir[i][0];
		if (inArea(dx, dy) && legal(dx, dy) && !gameover)
		{
			path.push_back(Pos(dx, dy));
			if (dx == food.x&&dy == food.y)
			{
				path.push_back(Pos(dx, dy));
				gameover = true;
				return gameover;
			}
			searcheat(dx, dy, food);
		}
	}
	return gameover;
}

DFS::~DFS()
{
}
