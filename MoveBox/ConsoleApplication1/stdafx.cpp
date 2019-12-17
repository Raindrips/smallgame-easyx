// stdafx.cpp : 只包括标准包含文件的源文件
// ConsoleApplication1.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
LevelPack* LevelPack::instance = nullptr;

LevelPack::LevelPack()
{
	levels.push_back({
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0, 4, 0, 1 },
			{ 1, 0, 0, 0, 2, 0, 0, 1 },
			{ 1, 4, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0, 2, 0, 1 },
			{ 1, 0, 0, 2, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0, 4, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
		}, 1, 1
	});
	levels.push_back({
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 0, 4, 0, 1 },
			{ 1, 0, 0, 0, 2, 0, 1, 1 },
			{ 1, 4, 1, 0, 0, 0, 0, 1 },
			{ 1, 1, 0, 0, 0, 2, 1, 1 },
			{ 1, 1, 0, 2, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1, 4, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
		}, 3, 3,
	});
	levels.push_back({
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 0, 0, 0, 4, 0, 1, 1 },
			{ 1, 0, 2, 0, 2, 1, 1, 1 },
			{ 1, 4, 1, 0, 0, 0, 1, 1 },
			{ 1, 1, 0, 0, 0, 2, 4, 1 },
			{ 1, 4, 0, 2, 2, 0, 1, 1 },
			{ 1, 0, 0, 0, 4, 0, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1 },
		}, 3, 3,
	});
}

LevelPack* LevelPack::getInstance()
{
	if (nullptr == instance)
	{
		instance = new LevelPack;
	}
	return instance;
}

Level LevelPack::get_level(int index)
{
	
	return levels[index%levels.size()];
}
