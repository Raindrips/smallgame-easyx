#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include <easyx.h>

enum CMD {
  NO,			//ʲô��û��
  RITATE,       //��ת
  LEFT,         //���
  RIGHT,        //�Ҽ�
  DOWN,         //����
  QUIT,         //�˳�
  SINK,         //�³�
};

//����״̬,��¼��ÿһ�����ӵ���Ϣ
struct BlockInfo {
  char id; //�ڼ�������
  char style; //��ʾ�Ƿ����еĵڼ���
  char x, y; //��ǰ���ӵ�λ��
};

//ÿ��ͼ����16�����ӱ�ʾ�� 0û������   1��ʾ 
struct Block {
  short dir[4];
  COLORREF color;
};

//1.��ͼ��
//���Ƶ�Ԫ��
void drawUnit(int x, int y, COLORREF co);

//��������ͼ��
void drawBlock(BlockInfo _block);

//����UI����
void drawGUI();

//���л���
void draw();

//�������鶯��
void clearAnima(int y);

//�����µ�ͼ��
void newBlock();

//������ת
void onRotate();

//����
void onDown();

//���
void fixed();

//�ƶ���ť
void moveBotton();

//��ʼ����Ϸ
void loadGame();

//��ʼ����Ϸ
void initGame(); 

//��Ϸ����
void gameOver();

//��ȡ���̰���
void getkey();

//���º���
void updata();

//��ʼ��Ϸ
void start();

#endif // !TETRIS_H
