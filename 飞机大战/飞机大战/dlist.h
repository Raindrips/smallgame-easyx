#pragma once	
#ifndef DLIST_H
#define DLIST_H

//链表节点
struct Node
{
	int x;
	int y;
	Node *prev;
	Node *next;
};

//双链表
struct dlist
{
	Node*front;
	Node*back;
	int size;
};

//节点初始化
Node* node_init(int x, int y);

//双链表的初始化
dlist* dlist_init();

//插入元素
void dlist_push(dlist *l, Node *node);

//删除指定一个结点
void dlist_pop(dlist *l, Node *node);

//清除所有结点
void dlist_clear(dlist *l);

//返回链表的大小
int dlist_size(dlist *l);

#endif	//DLIST_H

//ctrl+k ctrl+o   头文件和源文件切换
