// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <fstream>
using namespace std;

struct Level   //��ͼ�ؿ�
{
	std::vector<std::vector<int>> s;  //��ͼ����
	int x;	//�����λ��			
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