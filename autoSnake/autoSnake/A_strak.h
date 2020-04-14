#pragma once
#ifndef _A_STRAK_H
#define _A_STRAK_H
#include "snake_h.h"
#include <functional>
#include<deque>
#include <list>
#include<vector>
using std::vector;
using std::function;
using std::list;
using std::deque;
struct node
{
	node*parent;					//父节点
	int x;							//x,y坐标
	int y;							//节点的坐标
	int G;							//已经走过的值			起点到终点消耗的代价
	int H;							//预估的值				起点到终点预估的步数
	int getF(){ return G + H; };	//和值				    预估的值+已经走过的值
	node(int x, int y, int G, int H, node*p = nullptr)
		:x(x), y(y), G(G), H(H), parent(p){}
};
struct Position
{
	int x;
	int y;
	Position(){}
	Position(int x, int y) :x(x), y(y){}
};
class A_strak
{
	function<bool(int, int)> inArea;
	vector<node*> openList;				//高优先路径
	vector<node*> closeList;			//低优先路径
	int end_x;
	int end_y;
	int getH(int x, int y, int end_x, int end_y);
	bool isVisited(vector<node*>&ls, int x, int y);
	bool filer(int x, int y);
	bool head(int x, int y, int end_x, int end_y);
	void findNeighbor(node *n);
public:
	bool findhead(int x, int y, int end_x, int end_y, Position&path);
	bool findPath(int x, int y, int end_x, int end_y, deque<Position>&path);
	A_strak(function<bool(int, int)> inArea);
	~A_strak();
};
#endif


