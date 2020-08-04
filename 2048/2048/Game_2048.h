#pragma once

#include <easyx.h>
#include <conio.h>
#include <cstdio>

class Game_2048
{

  int arr[4][4];
  char ea[99];
  int score = 0;
  void init();

  void color(int i);

  int check();

  int matc(int make, int muak, int x);

  void swit(int x, int  y, int at);



  int step(int x, int y, int mx, int my);

  int Move(int x, int y);

  void random();

  bool isGameOver();

  int keyDown();

  void draw();

  void text();

  void updata();

  bool inArea(int x,int y);

  void mergeNum(int& v1, int& v2);

public:
  Game_2048();

  int start();

};

