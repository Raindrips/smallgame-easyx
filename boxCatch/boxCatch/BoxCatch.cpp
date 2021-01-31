#include "BoxCatch.h"
#include <ctime>
#include <algorithm>
int BoxCatch::getKeyDown() {
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || 
		GetAsyncKeyState('A') & 0x8000)
		return keyState::left;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000||
		GetAsyncKeyState('D') & 0x8000)
		return keyState::right;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		return keyState::quit;

	return keyState::empty;
}

void BoxCatch::update() {
	int speed = 10;
	int key = this->getKeyDown();

	switch (key)
	{
	case keyState::left:
		this->box.x -= speed;
		break;

	case keyState::right:
		this->box.x += speed;
		break;

	case keyState::quit:

		break;
	default:
		break;
	}

	if (this->box.x+100 > wid) {
		this->box.x = wid-100;
	}
	if (this->box.x < 0) {
		this->box.x = 0;
	}

	for (auto& ball : this->balls) {
		ball.y += ball.v;
		if (ball.y > this->hei) {
			ball = this->randomBall();
			continue;
		}
		if (ball.x > this->box.x &&
			ball.x < this->box.x + 100 &&
			ball.y > this->box.y &&
			ball.y < this->box.y+100) {
			ball = this->randomBall();
		}
	}
}

void BoxCatch::drawBall()
{
	for (const auto& ball : this->balls) {
		setfillcolor(ball.color);
		fillcircle(ball.x, ball.y, 12);
	}
}

void BoxCatch::drawBox()
{
	fillrectangle(this->box.x, this->box.y, this->box.x + 100, this->box.y + 40);
}

void BoxCatch::draw()
{
	BeginBatchDraw();
	cleardevice();
	this->drawBall();
	this->drawBox();
	EndBatchDraw();
}

void BoxCatch::countDown()
{
	clock_t c = clock();
}

Pos BoxCatch::randomBall()
{
	int x = rand() % wid;
	int y = rand() % 32;
	int v = 1 + rand() % 5;
	COLORREF color = 
		RGB(100+rand()%155, 100 + rand() % 155, 100 + rand() % 155);
	return  Pos{ x,y,v,color };
}

BoxCatch::BoxCatch()
{
	initgraph(wid, hei);
	srand(time(nullptr));
	this->init();
}

BoxCatch::~BoxCatch()
{
	closegraph();
}

void BoxCatch::run() {
	while (true) {
		this->update();
		this->draw();
		Sleep(1000 / 60);
	}
}

void BoxCatch::init()
{
	int i = 0;
	for (auto& ball : this->balls) {
		this->randomBall();
	}
	this->box.x = this->wid / 2;
	this->box.y = this->hei - 50;

	for (int i = 0; i < 100; i++) {
		this->balls.push_back(this->randomBall());
		this->balls.back().y -= rand() % hei;
	}
}
