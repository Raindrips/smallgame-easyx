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
	vector2r mapData;		//һ����ά����
	int len;

	void init();

	//ϴ���㷨
	void shuffle();
	
	//����ƶ�
	void randomMove();

	//�ж��Ƿ�����
	bool isOrder();

	DrawView* view;

	
};

