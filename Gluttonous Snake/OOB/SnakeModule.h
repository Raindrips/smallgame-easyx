#pragma once


#include <list>
#include <ctime>
using std::list;

//����
struct Position
{
	int x;
	int y;
	Position(int x = 0, int y = 0) :x(x), y(y) {}
};
//ö���� ����
enum direction
{
	UP = 0,	//��
	RIGHT,	//��
	DOWN,	//��
	LEFT,	//��
};

//̰����
class Snake
{
private:
	list<Position> snake;  //�ߵ�����
	direction dir_send, dir_recv;			//���ƶ��ķ���

	int wid, hei;
	int maxX, maxY;

	Position food;

	const int PIX = 20;	//����Ĵ�С
	const int LEN = 9;  //�ߵĳ�ʶ����
public:

	Snake(int wid = 480, int hei = 640);
	~Snake();

	void start();

protected:
	//��ʼ����Ϸ
	void init();

	void _rect(int x, int y);

	void spawnNewFood();

	void move();

	void control();

	bool isEatFood();

	bool isGameOver();

	void draw();

};

