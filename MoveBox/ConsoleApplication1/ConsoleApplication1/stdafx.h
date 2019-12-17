
#pragma once
#include <vector>
using namespace std;

struct Level   //��ͼ�ؿ�
{
	vector<vector<int>> s;  //��ͼ����
	int x;	//�����λ��			
	int y;
};

class LevelPack
{
protected:
	LevelPack();
	static LevelPack *instance;
	vector<Level> levels;
public:
	static LevelPack* getInstance();

	Level get_level(int index);
};


