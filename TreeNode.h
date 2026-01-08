#pragma once
typedef int ElemType;

class TreeNode
{
public:
	ElemType parent;
	ElemType data;

	TreeNode() :data(0), parent(-1) {}
	TreeNode(ElemType p, ElemType val) :parent(p), data(val) {}
};

