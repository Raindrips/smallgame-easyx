// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <fstream>
using namespace std;

struct Level   //地图关卡
{
	std::vector<std::vector<int>> s;  //地图数据
	int x;	//人物的位置			
	int y;
};

class EditLevels
{
	void set_level(Level& level,int n)
	{
		fstream fs("");
	}

	Level get_level(int n)
	{
		
	}
};