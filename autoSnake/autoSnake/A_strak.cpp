#include "A_strak.h"


int A_strak::getH(int x, int y, int end_x, int end_y)
{
	return std::abs(end_x - x) + std::abs(end_y - y);
}

bool A_strak::isVisited(vector<node*>&ls, int x, int y)
{
	for (int i = 0; i < ls.size(); i++)
	{
		if (ls[i]->x == x&&ls[i]->y == y)
		{
			return true;
		}
	}
	return false;
}

bool A_strak::filer(int x, int y)
{
	if (isVisited(closeList, x, y)||isVisited(openList,x,y))
	{
		return false;
	}
	if (bool(inArea) && !inArea(x, y))
	{
		return false;
	}
	return true;
}

void A_strak::findNeighbor(node *n)
{
	static vector<Position> dir = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	for (auto di : dir)
	{
		di.x += n->x;
		di.y += n->y;
		if (filer(di.x, di.y))
		{
			auto H = getH(di.x, di.y, end_x, end_y);
			openList.push_back(new node(di.x, di.y, n->G + 1, H, n));
		}
	}
}


bool A_strak::head(int x, int y,int end_x,int end_y)
{
	deque<Position>path;
	if (!inArea(x, y))
	{
		return false;
	}
	if (findPath(x, y, end_x, end_y, path))
	{
		std::cout << x << " " << y << std::endl;
		std::cout << end_x << " " << end_y << std::endl;
		return true;
	}
	return false;
}
bool A_strak::findhead(int x, int y, int end_x, int end_y,Position&path)
{
	this->end_x = end_x;
	this->end_y = end_y;
	vector<node*> p;
	bool is = false;
	static vector<Position> dir1 = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	for (auto di : dir1)
	{
		di.x += x;
		di.y += y;
		if (di.x == end_x&&di.y == end_y)
		{
			p.push_back(new node(di.x, di.y, 0, 0));
			is = true;
			continue;
		}
		if (head(di.x, di.y,end_x,end_y))
		{
			auto H = getH(di.x, di.y, end_x, end_y);
			p.push_back(new node(di.x, di.y, 1, H));
		}
	}
	node*min = nullptr;
	for (int i = p.size() - 1; i >= 0; i--)
	{
		auto n = p[i];
		if (!min || min->getF() < n->getF())
		{
			min = n;
		}
	}
	if (is&&min->x!=end_x&&min->y!=end_y)
	{
		deque<Position> p1;
		if (!findPath(min->x, min->y, end_x, end_y, p1))
		{
			min->x = end_x;
			min->y = end_y;
		}
	}
	if (min != nullptr)
	{
		path.x = min->x;
		path.y = min->y;
		for (auto n : p)			//销毁open路径节点
		{
			delete n;
		}
		p.clear();
		return true;
	}
	for (auto n : p)			//销毁open路径节点
	{
		delete n;
	}
	p.clear();
	return false;
}
bool A_strak::findPath(int x, int y, int end_x, int end_y, deque<Position>&path)
{
	bool judge = false;
	this->end_x = end_x;
	this->end_y = end_y;
	int H = getH(x, y, end_x, end_y);
	closeList.push_back(new node(x, y, 0, H));
	node*endgeme = nullptr;
	int count = 0;
	while (count < closeList.size())
	{
		count = closeList.size();
		node*min = nullptr;
		findNeighbor(closeList.back());
		int minIndex = 0;
		for (int i = openList.size() - 1; i >= 0; i--)
		{
			auto n = openList[i];
			if (n->x == end_x&&n->y == end_y)
			{
				endgeme = n;
				break;
			}
			if (!min || min->getF() > n->getF())
			{
				min = n;
				minIndex = i;
			}
			if (i == 0)
			{
				openList.erase(openList.begin() + minIndex);
			}
		}
		if (endgeme)
		{
			break;
		}
		if (min == nullptr)
		{
			continue;
		}
		closeList.push_back(min);
	}
	if (endgeme)
	{
		list<Position> li;
		while (endgeme)
		{
			li.push_back(Position(endgeme->x, endgeme->y));
			endgeme = endgeme->parent;
		}
		path.assign(li.rbegin(), li.rend());
		judge = true;
	}
	for (auto n : openList)			//销毁open路径节点
	{
		delete n;
	}
	openList.clear();
	for (auto n : closeList)		//销毁close路径节点
	{
		delete n;
	}
	closeList.clear();
	return judge;
}
A_strak::A_strak(function<bool(int, int)> inArea) :inArea(inArea)
{
}
A_strak::~A_strak()
{
}