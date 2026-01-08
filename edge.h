#pragma once
#include"node.h"
class edge
{
private:
	int weight;
	node* from;
	node* to;
public:
	edge(int w, node* f, node* t) :weight(w), from(f), to(t) {}
	// 增加访问器方法
	int getWeight() const { return weight; }
	node* getFrom() const { return from; }
	node* getTo() const { return to; }
};

