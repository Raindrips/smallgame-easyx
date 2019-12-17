// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <iostream>
#include  <vector>



using vmap = std::vector < std::vector<int>>;
struct Level
{
	vmap vm;
	Level(int maxX, int maxY)
	{
		vm.resize(maxY, std::vector<int>(maxX, 0));
			
	}
	void setLevel()
	{
		
	}

	vmap getlevel()
	{
		
	}
};