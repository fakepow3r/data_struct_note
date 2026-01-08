#pragma once
typedef int ElemType;
class BiTreeNode
{
public:
	ElemType val;
	BiTreeNode* left;
	BiTreeNode* right;
	BiTreeNode() : val(0), left(nullptr), right(nullptr) {}
	BiTreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	BiTreeNode(int x, BiTreeNode* left,BiTreeNode* right) : val(x), left(left), right(right) {}
	~BiTreeNode() {
		delete left;
		delete right;
	}
};

