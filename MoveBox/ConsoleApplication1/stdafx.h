
#pragma once
#include <vector>
using namespace std;

struct Level   //地图关卡
{
	vector<vector<int>> s;  //地图数据
	int x;	//人物的位置			
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


