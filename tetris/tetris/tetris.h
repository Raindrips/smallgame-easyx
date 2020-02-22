#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include <easyx.h>

enum CMD {
  NO,			//什么都没按
  RITATE,       //旋转
  LEFT,         //左键
  RIGHT,        //右键
  DOWN,         //下落
  QUIT,         //退出
  SINK,         //下沉
};

//操作状态,记录了每一个格子的信息
struct BlockInfo {
  char id; //第几个方块
  char style; //表示是方块中的第几个
  char x, y; //当前格子的位置
};

//每个图形用16个格子表示， 0没有内容   1显示 
struct Block {
  short dir[4];
  COLORREF color;
};

//1.画图形
//绘制单元格
void drawUnit(int x, int y, COLORREF co);

//绘制整体图形
void drawBlock(BlockInfo _block);

//绘制UI界面
void drawGUI();

//所有绘制
void draw();

//消除方块动画
void clearAnima(int y);

//生成新的图形
void newBlock();

//方块旋转
void onRotate();

//下落
void onDown();

//填充
void fixed();

//移动按钮
void moveBotton();

//初始化游戏
void loadGame();

//开始新游戏
void initGame(); 

//游戏结束
void gameOver();

//获取键盘按下
void getkey();

//更新函数
void updata();

//开始游戏
void start();

#endif // !TETRIS_H
