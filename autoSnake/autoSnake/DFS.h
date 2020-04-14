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
	bool legal(int x, int y);//�ж��Ƿ����߹���·��
	bool gameover;//�ж��Ƿ񵽴��յ�
public:
	DFS(function<bool(int, int)> inArea);
	void find(int x, int y, Pos &food, function<bool(int, int)> inArea);//��ʼ����
	deque<Pos>path;
	bool searcheat(int x, int y, Pos &food);//����ʳ��
	~DFS();
};
#endif // !1

