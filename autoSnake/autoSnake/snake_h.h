#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <iostream>
#include <functional>
#include<easyx.h>
#include<vector>
#include <ctime>
#include<cstdlib>
#include <deque>
#include"A_strak.h"
using std::vector;
using std::function;
using std::deque;
//����
struct Pos
{
	int x;
	int y;
	Pos();
	Pos(int x, int y);
};
//����
class A_strak;
struct Position;
class Snake
{
	int map_x;//��ͼx����
	int map_y;//��ͼy����
	int size;//��ͼ�������Ĵ�С
	bool _null;//�ж������Ƿ�Ϊ��
	Pos snake_h;//��ͷ
	Pos food;//ʳ������
	Pos tail;//��β����
	deque<Pos*>snake_b;//����
	vector<vector<int>>gedgame_map();
public:
	//template<class Position>
	int snake_bsize();//���������С
	
	bool findtail(deque<Position>path, A_strak strak);//�ж��߳���ʳ����ܲ��������Լ���β
	int gett_x();//��ȡ��βx����
	int gett_y();//��ȡ��βy����
	Snake(int map_x, int map_y, vector<vector<int>>game_map);
	int getsize();
	void initfood();//��ʼ��ʳ������
	Pos getfood();
	Pos getsnake_h();
	function<bool(int, int)> inArea;
	vector<vector<int>>game_map;//��ͼ
	int gets_x();//��ȡ��ͷX����
	int gets_y();//��ȡ��ͷy����
	int getf_x();
	int getf_y();
	void getsnake();//��ʼ��������
	void mobile_s(int x, int y);//�ƶ���
	void init();
	~Snake();
};
#endif // !_SNAKE_H_

