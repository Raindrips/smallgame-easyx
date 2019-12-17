// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ConsoleApplication1.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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
