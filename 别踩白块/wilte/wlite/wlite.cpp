// wlite.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <easyx.h>

class Rect {
  
};

class Game {
public:

  Game() {
	initgraph(wid, hei);

  }

private:
  int wid=640,hei=480;
  void init() {

  }
  ~Game() {
	closegraph();
  }
};

int main()
{
    std::cout << "Hello World!\n";
}
