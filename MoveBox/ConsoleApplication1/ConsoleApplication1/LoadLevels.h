#pragma once
#include "stdafx.h"
class LoadLevels
{
public:
	LevelPack *level;
	LoadLevels();
	void set_levels(int n);
	Level get_levels(int n);

	~LoadLevels();
};

