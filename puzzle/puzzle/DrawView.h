#pragma once

#include <string>
#include "easyx.h"
#include "dir.h"

class DrawView
{
public:
	DrawView(vector2r &data, const int len);

	void initPic(std::wstring path);

	void update();

	eDir onTouch();

	void moveDir(eDir dir);

	bool inAear(int x, int y);

	void findIndex();

private:
	const int WIDTH = 600;						
	vector2r &data;
	const int LEN;
	mutable int size;
	mutable int index;
	std::vector<IMAGE> pic;

	int currentX;
	int currentY;

	void draw();
	void text();
	

};

