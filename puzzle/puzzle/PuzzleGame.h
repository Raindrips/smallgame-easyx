#pragma once

#include "dir.h"

class DrawView;

class PuzzleGame
{
public:
	PuzzleGame(int len);
	~PuzzleGame();
	void runGame();
private:
	vector2r mapData;		//一个二维数组
	int len;

	void init();

	//洗牌算法
	void shuffle();
	
	//随机移动
	void randomMove();

	//判断是否有序
	bool isOrder();

	DrawView* view;

	
};

