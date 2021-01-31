#pragma once
#include <easyx.h>
#include <vector>
enum keyState {
	empty = -1,
	left = 1 << 0,
	right = 1 << 1,
	quit = 1 <<2,
};

struct Pos {
	int x;
	int y;
	int v;
	COLORREF color;
};

class BoxCatch
{
public:
	BoxCatch();
	~BoxCatch();
	void run();
private:
	
	void init();

	int getKeyDown();

	void update();

	
	void drawBall();
	void drawBox();
	void draw();

	void countDown();

	Pos randomBall();

	std::vector<Pos> balls;
	const int wid = 800;
	const int hei = 600;
	Pos box;
	int score;

};

