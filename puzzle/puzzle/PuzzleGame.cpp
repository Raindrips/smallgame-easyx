#include "PuzzleGame.h"
#include "DrawView.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <random>
using namespace std;
void PuzzleGame::init() {
	int id = 0;
	for (int i = 0; i < this->len; ++i) {
		for (int j = 0; j < this->len; j++) {
			mapData[i][j] = id++;
		}
	}
}
//ϴ���㷨
void PuzzleGame::shuffle() {
	random_device rd;
	int tempArr[9] = { 0,1,2,3,4,5,6,7,8 };
	for (size_t i = 0; i < this->len; i++) {
		int r = rd() % (this->len*this->len);
		std::swap(tempArr[i], tempArr[r]);
	}
	int id = 0;
	//��ֵ
	for (int i = 0; i < this->len; ++i) {
		for (int j = 0; j < this->len; j++) {
			mapData[i][j] = tempArr[id];
			id++;
		}
	}
}

void PuzzleGame::randomMove() {
	random_device r; 
	size_t times =  100;		//����ƶ��Ĵ��� 100
	for (size_t i = 0; i < times; i++) {
		eDir dir = eDir(r() % 4);		//0~3֮��
		this->view->findIndex();
		this->view->moveDir(dir);		
		this->view->update();
		//Sleep(16);
	}
	
}

//�ж��Ƿ�����
bool PuzzleGame::isOrder() {
	int t = -1;
	for (size_t i = 0; i < this->len; i++) {
		for (size_t j = 0; j < this->len; j++) {
			if (t > mapData[i][j]) {
				return false;
			}
			t = mapData[i][j];
		}
	}
	return true;
}

PuzzleGame::PuzzleGame(int len) :len(len) {
	mapData.resize(len, vector<int>(len));
	
	this->init();
	view = new DrawView(mapData,len);
	view->initPic(L"bg.png");
	view->update();
	Sleep(1600);
	//this->shuffle();		//ϴ���㷨����˳��
	this->randomMove();		//����ƶ�
	


}

PuzzleGame::~PuzzleGame() {
	delete view;
}

void PuzzleGame::runGame() {
	while (true) {		
		eDir dir=view->onTouch();
		view->moveDir(dir);
		view->update();
		if (this->isOrder()) {
			getchar();
			break;
		}
	}
}
