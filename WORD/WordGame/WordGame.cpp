//打字游戏  1.1

#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <easyx.h>
#include <vector>
#include <time.h>
#include <list>
#include <conio.h>

using namespace std;

// 计算fps
#define FPS_COUNT 60
float getFps()
{

  static int i = 0;
  static int oldTime = GetTickCount();
  static float fps;

  if (i > FPS_COUNT)
  {
	i = 0;
	int newTime = GetTickCount();
	int elapsedTime = newTime - oldTime;
	fps = FPS_COUNT / (elapsedTime / 1000.0f);
	oldTime = newTime;
  }
  i++;
  return fps;
}

struct Word
{
  float x;
  float y;
  char word;
  float speed;
};
class WordGame {
  int wid, hei;
  list<Word> words;
  int level = 1;
  int score = 0;
  char _getWord() {
	int n = rand() % 4 == 0 ? 'a' - 'A' : 0;

	return rand() % 26 + 'a' - n;
  }

  Word getW() {
	Word w;
	w.word = _getWord();
	w.x = rand() % (wid - 15);
	w.y = 0;
	w.speed = 0.5 + level * 0.5;
	return w;
  }

  void _init() {
	LOGFONT* font = new LOGFONT;
	gettextstyle(font);
	font->lfHeight = 30;
	strcpy(font->lfFaceName, "consolas");
	setbkmode(TRANSPARENT);
	settextstyle(font);
	words.push_back(getW());
  }

  void _update() {
	static int times = 0;
	for (auto& w : words)
	{
	  w.y += w.speed;
	  if (w.y > hei)
	  {
		score = (score - 10 > 0 ? score - 10 : 0);
	  }
	}
	if (times >= 70 - level * 10)
	{
	  times = 0;
	  words.push_back(getW());
	}
	times++;
  }

  void _draw_fps() {
	static char str[10];
	sprintf(str, "%.2f", getFps());
	outtext(str);
  }
  void _drawWord() {
	BYTE depth = 0xff;
	settextcolor(RGB(0, depth, 0));
	for (auto w : words)
	{

	  if (w.word >= 'a' && w.word <= 'z')
		settextcolor(RGB(0, depth, 0));
	  else
		settextcolor(RGB(0, depth, depth));

	  char s[2] = { 0 };
	  s[0] = w.word;
	  outtextxy(w.x, w.y, s);
	}
  }

  void _drawScore() {
	static char str[12];
	settextcolor(0xffffff);
	sprintf(str, "score:%d", score);
	outtext(str);
  }
  void _draw() {
	BeginBatchDraw();
	cleardevice();
	_drawScore();
	//_draw_fps();
	_drawWord();

	EndBatchDraw();
  }

  void _play() {
	if (_kbhit())
	{
	  int key = _getch();
	  for (list<Word>::iterator i = words.begin(); i != words.end(); i++)
	  {
		if (i->word == key)
		{
		  words.erase(i);
		  score++;
		  level = _levelUp();
		  return;
		}
	  }
	  score=score-1<0?score:score-1;
	}
  }

  int _levelUp() {
	return score / 30 + 1;
  }

public:
  WordGame(int wid, int hei) :wid(wid), hei(hei) {
	initgraph(wid, hei);
	srand(time(NULL));
  }
  void run() {
	_init();
	while (true)
	{
	  _update();
	  _play();
	  _draw();
	  Sleep(15);
	}
  }
};


int main(int a) {
  WordGame wg(640, 480);
  wg.run();
}
