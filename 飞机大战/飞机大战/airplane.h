#pragma once

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "dlist.h"

//��ʼ����Ϸ
void load();

//��ʼ������
void init();

//��ʼ��Ϸ
void start();

//��������
void update();

//���ƻ���
void draw();

//��Ϸ����
void control();

//�ж���Ϸ�Ƿ����
bool isGameOver();

//���ɵл�
void spawnEnemy();

//�����ӵ�
void spawnBullet();

//������Ч�ķɻ����ӵ�
void destroy();

//�ӵ��Ƿ���л�������ײ
void bulletCollide();

//�ɻ���ײ
bool planeCollide(const Node *n1, const Node *n2);


#endif
