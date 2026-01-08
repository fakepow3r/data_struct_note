#pragma once
#include<vector>
#include"edge.h"
#include<iostream>
class node
{
private:
	int val;
	int in;
	int out;
	std::vector<node*> next;
	std::vector<edge*> edges;
public:
	node(int x) :val(x), in(0), out(0), next({}), edges({}) {}
	// 增加访问器方法（重要：解决私有成员访问问题）
	int getVal() const { return val; }
	int getIn() const { return in; }
	int getOut() const { return out; }
	const std::vector<node*>& getNext() const { return next; }
	const std::vector<edge*>& getEdges() const { return edges; }
	// 增加修改器方法（用于构建图）
	void addNext(node* n) {
		next.push_back(n);
		out++;  // 出度+1
		n->in++; // 邻接节点入度+1
	}
	void addEdge(edge* e) { edges.push_back(e); }
};

