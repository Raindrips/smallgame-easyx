// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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