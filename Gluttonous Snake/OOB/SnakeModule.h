#pragma once


#include <list>
#include <ctime>
using std::list;

//坐标
struct Position
{
	int x;
	int y;
	Position(int x = 0, int y = 0) :x(x), y(y) {}
};
//枚举类 方向
enum direction
{
	UP = 0,	//上
	RIGHT,	//右
	DOWN,	//下
	LEFT,	//左
};

//贪吃蛇
class Snake
{
private:
	list<Position> snake;  //蛇的身体
	direction dir_send, dir_recv;			//蛇移动的方向

	int wid, hei;
	int maxX, maxY;

	Position food;

	const int PIX = 20;	//方块的大小
	const int LEN = 9;  //蛇的初识长度
public:

	Snake(int wid = 480, int hei = 640);
	~Snake();

	void start();

protected:
	//初始化游戏
	void init();

	void _rect(int x, int y);

	void spawnNewFood();

	void move();

	void control();

	bool isEatFood();

	bool isGameOver();

	void draw();

};

