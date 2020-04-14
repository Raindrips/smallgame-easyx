#include<iostream>
#include "A_strak.h"
#include "snake_h.h"
#include "DFS.h"
#define N 30
using namespace std;

void text()
{
	vector<vector<int>>vec(N);
	for (int i = 0; i < N; i++)
	{
		vec[i].assign(N, 0);
	}

	Snake s(630, 630, vec);
	DFS d(s.inArea);
	s.getsnake();
	s.initfood();

	d.find(s.gets_x(), s.gets_y(), s.getfood(), s.inArea);
	//vector<vector<int>>game_map = s.getgame_map();

	while (1)
	{
		s.init();
		if (d.path.size() != 0)
			d.path.pop_front();
		else
			break;
		//system("pause");
		for (auto pos : d.path)
		{
			s.mobile_s(pos.x, pos.y);

			cleardevice();
			s.init();
			//if (pos.x == s.gets_x()&&pos.y==s.gets_y())
			s.init();
			Sleep(10);
		}
		s.initfood();
		s.init();
		d.path.clear();
		d.find(s.gets_x(), s.gets_y(), s.getfood(), s.inArea);
	}
}
void text2()
{
	vector<vector<int>>vec(N);
	for (int i = 0; i < N; i++)
	{
		vec[i].assign(N, 0);
	}
	Snake s(630, 630, vec);
	A_strak strak(s.inArea);
	deque<Position> path;
	s.getsnake();
	s.initfood();
	strak.findPath(s.gets_x(), s.gets_y(), s.getf_x(), s.getf_y(), path);
	s.init();
	while (1)
	{
		path.pop_front();
		for (auto pos : path)
		{
			s.mobile_s(pos.x, pos.y);
			cleardevice();
			s.init();
			/*if (s.getf_x() == s.gets_x() && s.getf_y() == s.gets_y())
			{
			break;
			}*/
		}
		s.initfood();
		path.clear();
		s.init();
		while (true)
		{
			if (strak.findPath(s.gets_x(), s.gets_y(), s.getf_x(), s.getf_y(), path))
			{
				if (s.findtail(path, strak))
				{
					break;
				}
				else
				{
					path.clear();
					Position p;
					if (strak.findhead(s.gets_x(), s.gets_y(), s.gett_x(), s.gett_y(), p))
					{
						cout << "吃的到食物找蛇尾巴" << endl;
						s.mobile_s(p.x, p.y);
						cleardevice();
						s.init();
					}
				}
			}
			else
			{
				path.clear();
				Position p;
				if (strak.findhead(s.gets_x(), s.gets_y(), s.gett_x(), s.gett_y(), p))
				{
					cout << "吃的到食物找蛇尾巴" << endl;
					s.mobile_s(p.x, p.y);
					cleardevice();
					s.init();
				}
			}
		}
	}
}
int main()
{
	//text();
	text2();
	system("pause");
	return 0;
}