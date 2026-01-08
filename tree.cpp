// tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include "Tree.h"
#include<unordered_map>
#include<unordered_set>
using namespace std;
//结点：树中的一个独立单元
//结点的度：结点拥有的子树称为结点的度
//树的度：树内各节点度的最大值
//叶子：度为0的结点或终端节点
//非终端结点：度不为0的结点
//双亲和孩子：结点的子树的根称为该节点的孩子，相应地，该结点称为孩子的双亲
//层次：从根开始定义
//性质一：树中所有节点数等于结点所有的度数之和加一
//性质二：对于度为m的树，第i层至多有m的i-1次方个结点
/*Tree::Tree()//初始化 
{
	size = 0;
	maxSize = 10;
	rootIndex = -1;
	nodes = new TreeNode[maxSize];
}*/
Tree::~Tree() {
	//    clear(root);
	delete root;
	root = NULL;
}
//插入根节点
/*void Tree::insert_root(ElemType val)
{
	if (size == 0) {
		nodes[0] = TreeNode(-1, val);
		rootIndex = 0;
		size = 1;
	}
	else {
		nodes[rootIndex].data = val;
	}
}*/
//扩容
/*void Tree::resize()
{
	int new_maxSize = 2 * maxSize;
	TreeNode* new_nodes = new TreeNode[new_maxSize];
	for (int i = 0; i < size; i++) {
		new_nodes[i] = nodes[i];
	}
	delete[]nodes;
	nodes = new_nodes;
	maxSize = new_maxSize;
}*/
//bool Tree::isempty() {
	//return size == 0;
//}
/*void Tree::insert_child(ElemType key, ElemType p)
{
	if (size >= maxSize) {
		resize();
	}
	int parent_index = find_parent(p);
	if (parent_index == -1) {
		return;
	}
	else {
		nodes[size] = TreeNode(parent_index, key);
		size++;
	}
}*/
/*ElemType Tree::find_parent(ElemType parent)
{
	for (int i = 0; i < size; i++) {
		if (parent == nodes[i].data) {
			return i;
		}
	}
	return -1;
}*/
void Tree::preOrder(BiTreeNode* T) {
	if (T == NULL) {
		return;
	}
	cout << T->val << endl;
	preOrder(T->left);
	preOrder(T->right);
}
//递归法，元素
void Tree::inOrder(BiTreeNode* T,vector<ElemType>&res) {
	if (T == NULL) {
		return;
	}
	inOrder(T->left,res);
	res.push_back(T->val);
	cout << T->val << endl;
	inOrder(T->right,res);
}
bool Tree::isBST() {
	int preValue = INT_MIN;
	return isBST(root,preValue);
}
bool Tree::isBST(BiTreeNode*T,int&preValue) {
	if (T == NULL)return true;
	bool preCheck = isBST(T->left,preValue);
	if (!preCheck) {
		return false;
	}
	//原中序遍历打印时机替换成比较时机
	if (T->val <= preValue) {
		return false;
	}
	else {
		preValue = T->val;
	}
	return isBST(T->right,preValue);
}

bool Tree::isBST_rec() {
	return proc(root).isBS;
}
retType Tree::proc(BiTreeNode*root) {
	//满足一下四个条件：
	//1.左树为搜索二叉树
	//2.右树为搜索二叉树
	//3.左树最大值小于root->val
	//4.右树最小值要大于root->val
	if (root == NULL) { return retType(); }
	retType l = proc(root->left);
	retType r = proc(root->right);

	int M=root->val;
	int m=root->val;
	if (l.Max != INT_MIN) {
		m = min(m, l.Min);
		M = max(M, l.Max);
	}
	if (l.Min != INT_MIN) {
		m = min(m, r.Min);
		M = max(M, r.Max);
	}
	bool isB=true;
	if (l.Max != INT_MIN&&(!l.isBS||l.Max>=root->val)) {
		isB = false;
	}
	if (r.Min != INT_MIN && (!r.isBS||r.Min<=root->val)) {
		isB = false;
	}

	return retType(isB, M, m);
}
void Tree::non_recur_inorder() {
	//一棵树的左边树全部进栈，一次弹出的过程中打印，然后再把这个结点的右子树进站，再以此弹出打印
}
vector<int> Tree::inorderTraversal(BiTreeNode* root) {
	vector<int>BiTree;
	inOrder(root, BiTree);
	return BiTree;
}

BiTreeNode* Tree::invertTree(BiTreeNode* root) {
	//递归吧
	//把一棵树反转就是左右孩子换位子,孩子换位子同理
	//先判空
	if (root == NULL)return NULL;
	BiTreeNode* left = invertTree(root->left);
	BiTreeNode* right = invertTree(root->right);
	root->left = right;
	root->right = left;
	return root;
}
//检查二叉树是否对称
bool Tree::order(BiTreeNode* r, BiTreeNode* l) {
	if (!r && !l)return true;
	if (!r || !l)return false;
	return r->val == l->val && order(r->left, l->right) && order(r->right, l->left);
}
bool Tree::isSymmetric(BiTreeNode* root) {
	return order(root->right, root->left);
}
//二叉树的直径

int Tree::maxdepth(BiTreeNode* root) {
	if (root == nullptr)return 0;
	int l = maxdepth(root->left);
	int r = maxdepth(root->right);
	int ans = max(ans, l + r + 1);
	return max(l, r) + 1;
}
int Tree::diameterOfBinaryTree() {
	//最大直径==父节点直径+1
	//右树最大深度+左树最大深度
	//深度==父节点深度+1，根节点深度为0
	int ans = 1;
	maxdepth(root);
	return ans - 1;
}
void Tree::non_recur_posorder() {
	//两个栈，一个用来收集，一个用来放结点
	//弹出一个cur
	//cur放入收栈
	//先左再右
	if (root == NULL) { return; }
	stack<BiTreeNode*> s;
	stack<BiTreeNode*> s_collect;
	s.push(root);
	while (!s.empty()) {
		BiTreeNode* cur = s.top();
		s.pop();
		s_collect.push(cur);
		if (cur->left) {
			s.push(cur->left);
		}
		if (cur->right) {
			s.push(cur->right);
		}
	}
	while (!s_collect.empty()) {
		BiTreeNode* cur = s_collect.top();
		s_collect.pop();
		cout << cur->val << endl;
	}
}
void Tree::non_recursive_preorder() {
	//1.从栈中弹出一个结点current
	//2.打印（处理）current
	//3.先把右结点压入栈中，然后把左压栈，如果有
	//4.周而复始
	if (root == NULL) { return; }
	stack<BiTreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		BiTreeNode* cur = s.top();
		s.pop();
		cout << cur->val << endl;
		if (cur->right) { s.push(cur->right); }
		if (cur->left) { s.push(cur->left); }
	}
	cout << endl;
}
void Tree::BFS(vector<vector<ElemType>>&res) {
	if (root== NULL) {
		return;
	}
	queue<BiTreeNode*> q;
	q.push(root);//头结点入队
	int width = 0;
	while (!q.empty()) {//开始循环，一层一层循环
		int level_size = q.size();//设置一个变量记录当前层的结点个数
		vector<ElemType> currentLevel;//用来存放当前层的结点值
		for (int i = 0; i < level_size; i++) {//循环levelsize次就是刚好把当前层所有结点都处理掉
			BiTreeNode* cur = q.front();//取出头结点
			q.pop();//移除队头，防止重复处理
			currentLevel.push_back(cur->val);//记录当前节点的值
			if (cur->left) { q.push(cur->left); }//如果该结点有左节点，加入队列
			if (cur->right) { q.push(cur->right); }//如果该结点有右节点，加入队列
		}
		width = max(level_size,width);
		res.push_back(currentLevel);//在遍历完这层以后，把这层的结果数组加入结果数组，然后开启下一层的处理
	}
	cout <<"树的最大宽度是："<<width << endl;
}
bool Tree::isCBT() {
	//1.任意结点如果有右节点没有左节点，则不是完全二叉树
	//2.如果遇到了第一个左右结点不全，则接下来的的结点都该是叶节点，否则false
	if (root == nullptr) {
		return true;
	}
	queue<BiTreeNode*>q;
	bool leaf = false;//在遇到左右两个孩子不双全的节点之前都是为false，一旦遇到后，立马变成true
	BiTreeNode* l = nullptr;
	BiTreeNode* r = nullptr;
	q.push(root);
	while (!q.empty()) {
		root = q.front();
		q.pop();
		l = root->left;
		r = root->right;
		if (
			//条件一：如果有右节点没有左节点，则不是完全二叉树
			(l==nullptr&&r!=NULL)
			||
			//条件二：遇到了孩子不双全的结点以后，且碰到了非叶节点的结点，直接返回false
			((l!=NULL&&r!=NULL)&&leaf)
			) {
			//满足以上任意一个条件，则不为1完全二叉树，因此两个条件用||。即或连接
			return false;
		}
		if (l) { q.push(l); }
		if (r) { q.push(r); }
		//每次判断是不是孩子双全,左右孩子有任意一个为空则把leaf的状态改为true
		if (r == NULL || l == NULL) {
			leaf = true;
		}
	}
	//在遍历完所有节点后没有返回false，则是cbt，返回true
	return true;
}

bool Tree::isBBT() {
	return process(root).first;
}
pair<bool,int> Tree::process(BiTreeNode* root) {
	if (root == NULL) {
		return { true, 0 };
	}
	auto le = process(root->left);
	auto ri = process(root->right);
	int height = max(le.second, ri.second) + 1;
	bool isBalanced =
		//1.左子树为平衡二叉树
		//2.右子树为平衡二叉树
		le.first && ri.first
		//3.|左高-右高|<=1
		&& abs(le.second - ri.second) < 2;
	return { isBalanced, height };
}
void Tree::build() {
	root = new BiTreeNode(1);
	root->left = new BiTreeNode(9);
	root->right = new BiTreeNode(20);
	root->right->left = new BiTreeNode(15);
	root->right->right = new BiTreeNode(7);
}
bool Tree::isF() {
	if (root == NULL)return true;
	info data = procF(root);
	return data.nodes == pow(2,data.height - 1);
}

info Tree::procF(BiTreeNode* root) {
	if (root == NULL)return info(0, 0);
	info l = procF(root->left);
	info r = procF(root->right);
	int height=max(l.height,r.height)+1;
	int node=l.nodes+r.nodes+1;
	return info(node, height);
}
BiTreeNode* Tree::lca(BiTreeNode* head, BiTreeNode* n1, BiTreeNode* n2) {
	unordered_map<BiTreeNode*, BiTreeNode*> fathermap;
	procL(head, fathermap);
	unordered_set<BiTreeNode*> n1_parent;//存储n1的所有祖先
	while (n1)//记录n1的所有祖先 
	{
		n1_parent.insert(n1);
		n1 = fathermap[n1];
	}
	n1_parent.insert(head);
	while (n2) {
		if (n1_parent.count(n2)) {
			return n2;//如果n2是n1的一个祖先节点，就返回n2
		}
		n2 = fathermap[n2];//n2不断往上窜，每次窜一层
	}
}
void Tree::procL(BiTreeNode* head ,unordered_map<BiTreeNode*, BiTreeNode*> &fathermap)//存储节点-》父节点 
{
	if (head == NULL)return;
	fathermap[head->left] = head;
	fathermap[head->right] = head;
	procL(head->left, fathermap);
	procL(head->right, fathermap);

}
BiTreeNode* Tree::lca_re(BiTreeNode* head, BiTreeNode* n1, BiTreeNode* n2) {
	if (head == nullptr || head == n1 || head == n2) {
		return head;
	}
	BiTreeNode* l = lca(head->left, n1, n2);
	BiTreeNode* r = lca(head->right, n1, n2);
	if (l != nullptr && r != nullptr) {
		return head;
	}
	return l != nullptr ? l : r;
}