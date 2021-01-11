#include "DrawView.h"

#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
DrawView::DrawView(vector2r& data, const int LEN)
	:data(data), LEN(LEN) {
	initgraph(WIDTH, WIDTH, EW_SHOWCONSOLE);
	this->pic.resize(data.size()*data.size());
	this->size = WIDTH / LEN;
	this->index = data.size()*data.size() - 1;
}

void DrawView::initPic(std::wstring path) {
	IMAGE tempImg;
	loadimage(&tempImg, path.data());

	SetWorkingImage(&tempImg);//设定当前绘图设备tempImg
	int num = 0;

	for (int i = 0; i < LEN; ++i) {
		for (int j = 0; j < LEN; j++) {
			getimage(&pic[num], j * size, i * size, size, size);//分割图片存入数组
			++num;
		}
	}
	SetWorkingImage(nullptr);
	//加载空白图片到数组最后一个位置
	loadimage(&pic[this->index], L"");

}

void DrawView::update() {
	this->draw();


}

eDir DrawView::onTouch() {
	MOUSEMSG m = GetMouseMsg();
	if (m.uMsg == WM_LBUTTONDOWN) {
		this->text();
		int x = m.x / this->size;
		int y = m.y / this->size;
		cout << x << y << endl;
		const int dir[4][2] = {
			{0,1},				//下
			{0,-1},				//上

			{1,0},				//右
			{-1,0},				//左
		};
		for (size_t i = 0; i < 4; i++) {

			int X = dir[i][0] + x;
			int Y = dir[i][1] + y;

			if (this->inAear(X, Y) && this->data[Y][X] == this->index) {
				this->currentX = X;
				this->currentY = Y;
				cout << "i=" << i << endl;
				return (eDir)i;
			}
		}
	}
	return eDir::null;
}

bool DrawView::inAear(int x, int y) {
	return !(x < 0 || x >= LEN || y < 0 || y >= LEN);
}

void DrawView::findIndex() {
	for (size_t i = 0; i < LEN; i++) {
		for (size_t j = 0; j < LEN; j++) {
			if (this->data[i][j]==this->index) {
				this->currentX = j;
				this->currentY = i;
				return;
			}
		}
	}
}

void DrawView::draw() {
	BeginBatchDraw();
	cleardevice();
	for (int i = 0; i < this->LEN; ++i) {
		for (int j = 0; j < this->LEN; ++j) {
			putimage(j * size, i * size, &pic[data[i][j]]);
		}
	}
	EndBatchDraw();
}

void DrawView::text() {
	system("cls");
	string str;
	for (int i = 0; i < this->LEN; ++i) {
		for (int j = 0; j < this->LEN; ++j) {
			str += to_string(data[i][j]) + " ";
		}
		str += '\n';
	}
	cout << str << endl << currentX << ":" << currentY << endl;
}

void DrawView::moveDir(eDir dir) {
	int X, Y;
	switch (dir) {
	case eDir::up:
		Y = currentY - 1;
		if (inAear(currentX, Y)) {
			swap(data[Y][currentX], data[currentY][currentX]);
		}
		break;
	case eDir::down:
		Y = currentY + 1;
		if (inAear(currentX, Y)) {
			swap(data[Y][currentX], data[currentY][currentX]);
		}
		break;
	case eDir::left:
		X = currentX - 1;
		if (inAear(X, currentY)) {
			swap(data[currentY][X], data[currentY][currentX]);
		}
		break;
	case eDir::right:
		X = currentX + 1;
		if (inAear(X, currentY)) {
			swap(data[currentY][X], data[currentY][currentX]);
			break;
		}
	}

};
