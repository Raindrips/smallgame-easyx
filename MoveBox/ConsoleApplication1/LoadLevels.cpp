#include "LoadLevels.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

LoadLevels::LoadLevels()
{
	level = LevelPack::getInstance();
}

void LoadLevels::set_levels(int n)
{

	string path;
	path = path + "levels/level" + to_string(n) + ".map";
	fstream fs(path, ios::out | ios::binary);

	auto l = level->get_level(n);
	fs.write((char*)&l.x, sizeof(l.x));
	fs.write((char*)&l.y, sizeof(l.y));
	for (size_t i = 0; i < l.s.size(); i++)
	{
		fs.write((char*)l.s[i].data(), l.s[i].capacity());
	}
	fs.close();
}

Level LoadLevels::get_levels(int n)
{

	string path;
	path = path + "levels/level" + to_string(n) + ".map";
	fstream fs(path, ios::in | ios::binary);
	Level l;
	l = level->get_level(n);
	fs.read((char*)&l.x, sizeof(l.x));
	fs.read((char*)&l.y, sizeof(l.y));
	
	for (size_t i = 0; i < l.s.size(); i++)
	{
		fs.read((char*)l.s[i].data(), l.s[i].capacity());
	}
	fs.close();
	return l;
}


LoadLevels::~LoadLevels()
{
}
