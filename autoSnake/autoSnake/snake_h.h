#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <iostream>
#include <functional>
#include<easyx.h>
#include<vector>
#include <ctime>
#include<cstdlib>
#include <deque>
#include"A_strak.h"
using std::vector;
using std::function;
using std::deque;
//坐标
struct Pos
{
	int x;
	int y;
	Pos();
	Pos(int x, int y);
};
//画蛇
class A_strak;
struct Position;
class Snake
{
	int map_x;//地图x坐标
	int map_y;//地图y坐标
	int size;//地图里的区块的大小
	bool _null;//判断蛇身是否为空
	Pos snake_h;//蛇头
	Pos food;//食物坐标
	Pos tail;//蛇尾坐标
	deque<Pos*>snake_b;//蛇身
	vector<vector<int>>gedgame_map();
public:
	//template<class Position>
	int snake_bsize();//返回蛇身大小
	
	bool findtail(deque<Position>path, A_strak strak);//判断蛇吃了食物后能不能碰到自己蛇尾
	int gett_x();//获取蛇尾x坐标
	int gett_y();//获取蛇尾y坐标
	Snake(int map_x, int map_y, vector<vector<int>>game_map);
	int getsize();
	void initfood();//初始化食物坐标
	Pos getfood();
	Pos getsnake_h();
	function<bool(int, int)> inArea;
	vector<vector<int>>game_map;//地图
	int gets_x();//获取蛇头X坐标
	int gets_y();//获取蛇头y坐标
	int getf_x();
	int getf_y();
	void getsnake();//初始化蛇坐标
	void mobile_s(int x, int y);//移动蛇
	void init();
	~Snake();
};
#endif // !_SNAKE_H_

