
#include "stdafx.h"
#include <easyx.h> 
#include <conio.h>
#include <stack>  //STL 栈   先进后出  后进先出
#include <list>
#include <iostream>

// https://easyx.cn/  图形库下载地址   
#include <vector>
#include "LoadLevels.h"
using namespace std;



//推箱子游戏
class MoveBox
{
protected:
	Level level;   //关卡
	int wid, hei;  //屏幕的宽高
	int sizeW, sizeH;  //每个图片的宽和高
	vector<IMAGE> images; //存放图像的动态数组

	LevelPack *pak; //所有的关卡

	stack<Level> history;  //用栈储存每次走过的路

	int step = 0;  //第几关

	//从文件中加载图片
	void getRes()
	{
		images.resize(6);

		loadimage(&images[0], _T("res/player.png"), sizeW, sizeH);
		loadimage(&images[1], _T("res/box.png"), sizeW, sizeH);

		loadimage(&images[2], _T("res/end.png"), sizeW, sizeH);
		loadimage(&images[3], _T("res/bk.jpg"), wid, hei);

		loadimage(&images[4], _T("res/wall.png"), sizeW, sizeH);
		loadimage(&images[5], _T("res/aims.png"), sizeW, sizeH);
	}

	void draw()
	{
		BeginBatchDraw();
		putimage(0, 0, &images[3]);
		for (size_t i = 0; i < level.s.size(); i++)
		{
			for (size_t j = 0; j < level.s[i].size(); ++j)
			{
				switch (level.s[i][j])
				{
				case 1:  //墙
					putimage(j*sizeW, i*sizeH, &images[4]);
					break;
				case 2:  //箱子
					putimage(j*sizeW, i*sizeH, &images[1]);
					break;
				case 4: //目的地
					putimage(j*sizeW, i*sizeH, &images[5]);
					break;
				case 6: //箱子+目的地
					putimage(j*sizeW, i*sizeH, &images[2]);
					break;
				}
			}
		}
		putimage(level.x*sizeW, level.y*sizeH, &images[0]);

		EndBatchDraw();
	}

	//人物移动
	void move(int mx, int my)
	{
		int newX = level.x + mx;
		int newY = level.y + my;
		//判断是否可以移动
		if (newX < 0 || newX >= level.s.size() ||
			newY < 0 || newY >= level.s.size() ||
			level.s[newY][newX] == 1)
		{
			return;
		}
		if (level.s[newY][newX] == 0 || level.s[newY][newX] == 4)
		{
			const Level newL = level;
			history.push(newL);
			level.x = newX;
			level.y = newY;
		}
		else if ((level.s[newY][newX] >> 1) & 1)
		{
			int toX = level.x + mx * 2;
			int toY = level.y + my * 2;
			if (level.s[toY][toX] == 0 || level.s[toY][toX] == 4)
			{
				const Level newL = level;
				history.push(newL);

				level.x = newX;
				level.y = newY;
				//0B -> 10B  100B -> 110B  
				//箱子位 置0
				level.s[newY][newX] &= ~(size_t)(1 << 1);
				//箱子位 置1
				level.s[toY][toX] |= 1 << 1;
			}
		}
	}
	//游戏控制
	void control()
	{
		int key = _getch();
		int mx = 0, my = 0;
		switch (key)
		{
		case 'w':
		case 'W':
			my--;
			break;
		case 's':
		case 'S':
			my++;
			break;
		case 'a':
		case 'A':
			mx--;
			break;
		case 'd':
		case 'D':
			mx++;
			break;

		case 'z':
		case 'Z':
			if (!history.empty()){
				level = history.top();
				history.pop();
			}
			return;
		case 'r':
		case 'R':
			init();
			return;
		}
		move(mx, my);
	}

	//判断是否完成一局
	bool isWin()
	{
		for (size_t i = 0; i < level.s.size(); i++)
		{
			for (size_t j = 0; j < level.s[i].size(); ++j)
			{
				if (level.s[i][j] == 4)
				{
					return false;
				}
			}
		}
		return true;
	}
	//0:可以走的路  1:墙  2(1>>1 10B):箱子		
	//4(1>>2 100B)目的地
	//2+4 110B:目的地和箱子重合
	void init()
	{

		level = pak->get_level(step);
		history = {};
	}
public:
	MoveBox(int wid, int hei) :wid(wid), hei(hei)
	{
		initgraph(wid, hei);
		pak = LevelPack::getInstance();
		init();
		sizeH = hei / level.s.size();
		sizeW = wid / level.s[0].size();


	}
	MoveBox(Level level, int wid, int hei) :level(level),wid(wid), hei(hei)
	{
		initgraph(wid, hei);
		pak = LevelPack::getInstance();
		
		sizeH = hei / level.s.size();
		sizeW = wid / level.s[0].size();


	}
	void runGame()
	{
		getRes();
		while (true)
		{
			draw();
			control();
			if (isWin())
			{
				draw();
				MessageBox(GetForegroundWindow(), _T("恭喜过关"), _T(""), MB_OK);
				step++;
				init();
			}

		}
	}
	~MoveBox()
	{
		closegraph();
	}

};

void test1()
{
	LoadLevels ll;
	ll.set_levels(1);
	ll.set_levels(2);
	ll.set_levels(3);
	Level m = ll.get_levels(1);
	cout << m.x << endl;
	cout << m.y << endl;

	for (size_t i = 0; i < m.s.size(); i++)
	{
		for (size_t j = 0; j < m.s[i].size(); j++)
		{
			cout << m.s[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	LoadLevels ll;
	MoveBox move_box(ll.get_levels(1),600, 600);
	move_box.runGame();
	//test1();
	return 0;
}

