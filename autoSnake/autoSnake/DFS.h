#pragma once
#ifndef _DFS_H_
#define _DFS_H_
#include "snake_h.h"
#include <functional>
#include <deque>
using std::function;
using std::deque;
class DFS
{
	function<bool(int, int)> inArea;
	bool legal(int x, int y);//判断是否是走过的路径
	bool gameover;//判断是否到达终点
public:
	DFS(function<bool(int, int)> inArea);
	void find(int x, int y, Pos &food, function<bool(int, int)> inArea);//开始查找
	deque<Pos>path;
	bool searcheat(int x, int y, Pos &food);//搜索食物
	~DFS();
};
#endif // !1

