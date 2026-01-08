#pragma once
//#include"TreeNode.h"
#include"BiTreeNode.h"
#include<vector>
using namespace std;
//typedef TreeNode* BiTree;
struct returnType{
	bool isBalanced;
	int height;
	returnType(bool isB, int hei) :isBalanced(isB), height(hei) {}
};
struct retType {
	bool isBS;
	int Max;
	int Min;
	retType():isBS(true),Max(INT_MIN),Min(INT_MAX){}
	retType(bool BS, int M, int m) :isBS(BS), Max(M), Min(m) {}
};
struct info {
	int nodes;
	int height;
	info(int no, int he) :nodes(no), height(he) {}
};

class Tree
{
private:
	//TreeNode* nodes;
	BiTreeNode* root;

	/*int size;
	int maxSize;
	int rootIndex;
	int ans;*/
	pair<bool, int> process(BiTreeNode* root);
public:
	Tree() :root(NULL) {};
	~Tree();
	//父亲表示法
	void insert_root(ElemType val);
	void insert_child(ElemType key, ElemType p);
	ElemType find_parent(ElemType parent);
	void resize();

	//孩子表示法：父节点用顺序表，每个服节点的孩子用链表
	//孩子兄弟表示法：一个节点包括数据，兄弟节点，孩子结点，孩子结点被占，就用站这个结点的结点的兄弟结点链接 

	bool isempty();
	//二叉树
	void build();
	void preOrder(BiTreeNode* T);//前序遍历
	void non_recursive_preorder();//非递归前序遍历
	void non_recur_posorder();
	void inOrder(BiTreeNode* T,vector<ElemType>&res);//中序遍历
	void non_recur_inorder();
	bool isBST();
	bool isBST(BiTreeNode*T,int&preValue);//是否为搜索二叉树
	bool isBST_rec();
	retType proc(BiTreeNode*root);//递归套路判断是否为搜索二叉树
	bool isCBT();//是否为完全二叉树
	bool isMBT();//是否为满二叉树，即2的深度次方-1是否等于所有节点的个数
	bool isBBT();//是否为平衡二叉树
	vector<int> inorderTraversal(BiTreeNode* root);
	BiTreeNode* invertTree(BiTreeNode* root);//反转
	bool order(BiTreeNode* r, BiTreeNode* l);//检查是否对称
	bool isSymmetric(BiTreeNode* root);
	int maxdepth(BiTreeNode* root);
	int diameterOfBinaryTree();
	void BFS( vector<vector<ElemType>>& res);//层序遍历
	bool isF();
	info procF(BiTreeNode* root);
	BiTreeNode* lca(BiTreeNode* head, BiTreeNode* n1, BiTreeNode* n2);
	void procL(BiTreeNode* head, unordered_map<BiTreeNode*, BiTreeNode*>& fathermap);
	BiTreeNode* lca_re(BiTreeNode* head, BiTreeNode* n1, BiTreeNode* n2);
};

