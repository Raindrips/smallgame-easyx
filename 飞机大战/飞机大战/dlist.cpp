
#include "dlist.h"
#include <stdlib.h>
#include <assert.h>

#define NEW(type) (type*)malloc(sizeof(type))

//链接两个双链表节点
void node_link(Node* n1, Node* n2)
{
	n1->next = n2;
	n2->prev = n1;
}

Node* node_init(int x, int y)
{
	Node* temp = NEW(Node);
	temp->x = x;
	temp->y = y;
	temp->prev = temp->next = NULL;
	return temp;
}

//双链表的初始化
dlist* dlist_init()
{
	dlist* temp = NEW(dlist);
	temp->front = temp->back = NULL;
	temp->size = 0;
	return temp;
}

//插入元素
void dlist_push(dlist *l, Node *node)
{
	if (l->front == NULL)			//第一次插入元素节点
	{
		l->front = node;
		l->back = l->front;
	}
	else
	{
		Node *temp = node;
		node_link(temp, l->front);
		l->front = temp;
	}
	l->size++;
}

//删除指定一个结点
void dlist_pop(dlist *l, Node *node)
{
	assert(l->front);
	if (node == l->front)		//删除头部
	{
		Node *t = l->front;
		l->front = l->front->next;
		if (l->front)
			l->front->prev = NULL;
		else
			l->back = NULL;
		free(t);
	}
	else if (node == l->back)	//删除尾部
	{
		Node *t = l->back;

		l->back = l->back->prev;
		if (l->back)
			l->back->next = NULL;
		else
			l->front = NULL;
		free(t);
	}
	else					//删除中间的
	{
		node_link(node->prev, node->next);
		free(node);
	}
	l->size--;
}

//清除所有结点
void dlist_clear(dlist *l)
{
	Node* t = l->front;
	while (t)
	{
		Node* n = t;
		t = t->next;
		free(n);
	}
	l->front = l->back = NULL;
	l->size = 0;
}

//返回链表的大小
int dlist_size(dlist *l)
{
	return l->size;
}