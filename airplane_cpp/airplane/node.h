#pragma once
#include <list>
#include <easyx.h>
#include <vector>
#include <ctime>
#include <conio.h>
#include <cstdlib>
using std::list;
using std::vector;
struct Vec2 {
  int x;
  int y;
  Vec2(int x, int y) :x(x), y(y) {}
};



class Airplan {
  int wid;
  int hei;
  vector<IMAGE>vimg;

  Vec2 plan = { 0,0 };
  list<Vec2> enemyPlan;
  list<Vec2> bullet;
  int grade = 0;
  int px = 40;

  TCHAR tc[30];

  void spawnBullet() {
	if (bullet.size() < 3)
	{
	  bullet.push_back(Vec2(plan.x, plan.y + 10));
	}
  }
  void destoryBullet() {
	for (auto it = bullet.begin(); it != bullet.end(); it++) {
	  if (it->y < 0)
	  {
		bullet.erase(it);
		break;
	  }
	}
  }
  void spawnEnemy() {
	static int x = 0;
	if (x >= 20)
	{
	  if (enemyPlan.size() < 5)
	  {
		enemyPlan.push_back(Vec2(std::rand() % (wid - px) + px / 2, 0));
	  }
	  x = 0;
	}
	x++;
  }
  void destoryEnemy() {
	for (auto it = enemyPlan.begin(); it != enemyPlan.end(); it++) {
	  if (it->y > hei)
	  {
		enemyPlan.erase(it);
		break;
	  }
	}
  }

  bool planeCollide(Vec2& v1, Vec2& v2) {
	int x = std::abs(v1.x - v2.x);
	int y = std::abs(v1.y - v2.y);
	return x < px && y < px;
  }

  void bulletCollide() {
	for (auto p = bullet.begin(); p != bullet.end(); p++) {
	  for (auto en = enemyPlan.begin(); en != enemyPlan.end(); en++) {
		if (planeCollide(*p, *en))
		{
		  bullet.erase(p);
		  enemyPlan.erase(en);
		  grade++;
		  return;
		}
	  }
	}
  }

  void updata() {
	for (auto& p : enemyPlan) {
	  p.y += 2;
	}
	for (auto& p : bullet) {
	  p.y -= 8;
	}
	bulletCollide();
	destoryEnemy();
	destoryBullet();

	spawnEnemy();
  }

  void control() {
	int speed = 3;
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
	  if (plan.y > px / 2)
		plan.y -= speed;

	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
	  if (plan.y < hei - px)
		plan.y += speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
	  if (plan.x < wid - px)
		plan.x += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
	  if (plan.x > 0)
		plan.x -= speed;
	}
	if (_kbhit())
	{
	  if (_getch() == (VK_SPACE))
	  {
		spawnBullet();
	  }
	}

  }

  bool isGameOver() {
	for (auto p : enemyPlan) {
	  if (planeCollide(plan, p))
		return true;
	}
	return false;
  }

  void draw() {
	BeginBatchDraw();
	cleardevice();
	for (auto p : enemyPlan) {
	  putimage(p.x, p.y, &vimg[0]);
	}
	for (auto p : bullet) {
	  putimage(p.x, p.y, &vimg[2]);
	}
	putimage(plan.x, plan.y, &vimg[1]);

	wsprintf(tc, _T("score:%d"), grade);
	outtextxy(wid / 2, px, tc);
	EndBatchDraw();
  }

  void init() {
	plan = { wid / 2,hei - px * 2 };
	bullet.clear();
	enemyPlan.clear();
	grade = 0;
  }

public:
  void start() {

	while (true)
	{
	  updata();
	  control();
	  draw();
	  if (isGameOver())
	  {
		if (MessageBox(GetForegroundWindow(), _T("是否重新开始游戏"), _T("游戏结束"), MB_YESNO) == IDYES)
		  init();
		else
		  break;
	  }
	  Sleep(15);
	}
  }
  Airplan(int wid, int hei) :wid(wid), hei(hei) {
	initgraph(wid, hei);
	vimg.resize(4);
	loadimage(&vimg[0], _T("res/1.jpg"), px, px);
	loadimage(&vimg[1], _T("res/2.jpg"), px, px);
	loadimage(&vimg[2], _T("res/3.jpg"), 20, 20);
	loadimage(&vimg[3], _T("res/4.jpg"), 500, 500);
	init();
  }

  ~Airplan() {
	closegraph();
  }
};