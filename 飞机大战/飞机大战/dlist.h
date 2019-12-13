#pragma once	
#ifndef DLIST_H
#define DLIST_H

//����ڵ�
struct Node
{
	int x;
	int y;
	Node *prev;
	Node *next;
};

//˫����
struct dlist
{
	Node*front;
	Node*back;
	int size;
};

//�ڵ��ʼ��
Node* node_init(int x, int y);

//˫����ĳ�ʼ��
dlist* dlist_init();

//����Ԫ��
void dlist_push(dlist *l, Node *node);

//ɾ��ָ��һ�����
void dlist_pop(dlist *l, Node *node);

//������н��
void dlist_clear(dlist *l);

//��������Ĵ�С
int dlist_size(dlist *l);

#endif	//DLIST_H

//ctrl+k ctrl+o   ͷ�ļ���Դ�ļ��л�
