#pragma once

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "dlist.h"

//初始化游戏
void load();

//初始化数据
void init();

//开始游戏
void start();

//更新数据
void update();

//绘制画面
void draw();

//游戏控制
void control();

//判断游戏是否结束
bool isGameOver();

//生成敌机
void spawnEnemy();

//生成子弹
void spawnBullet();

//销毁无效的飞机和子弹
void destroy();

//子弹是否与敌机发生碰撞
void bulletCollide();

//飞机碰撞
bool planeCollide(const Node *n1, const Node *n2);


#endif
