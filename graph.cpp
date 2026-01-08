#include "graph.h"
#include"myset.h"
#include<queue>
#include<vector>
#include<stack>
#include <set>
#include<cmath>
using namespace std;
void graph::bfs(node*n) {
	if (n == NULL) { return; }
	queue<node*> q;
	unordered_set<node*>visited;
	q.push(n);
	visited.insert(n);
	while (!q.empty()) {
		node* cur = q.front();
		q.pop();
		//以下为要进行的操作，此处为打印
		cout << cur->getVal() << endl;

		for (auto nextNode : cur->getNext()) {
			if (visited.find(nextNode) == visited.end())//如果cur的相邻节点没有被访问过，就把它放入q中，并且标记为已访问过
			{
				visited.insert(nextNode);
				q.push(nextNode);
			}
		}
		cout << endl;
	}
}
void graph::dfs(node* n) {
	if (n == nullptr)return;
	unordered_set<node*> visited;
	stack<node*> s;
	s.push(n);
	visited.insert(n);
	//对初始节点的操作，此处为打印
	cout << n->getVal();
	while (!s.empty()) {
		//弹出栈顶，然后遍历栈顶的next，找到一个未被访问过的节点
		// 然后把之前弹出的结点和这个结点一起压入栈
		//标记这个相邻节点为已访问，然后对其进行访问
		//然后直接退出遍历，重新开始遍历此时的栈顶
		node* cur = s.top();
		s.pop();
		for (auto &next : cur->getNext()) {
			if (visited.find(next) == visited.end()) {
				s.push(cur);
				s.push(next);
				visited.insert(next);
				cout << next->getVal();
				break;
			}
		}

	}
}
vector<node*> graph::sortedtopology(graph* g) {
	//key:某一个node
	//value:剩余的入度
	unordered_map<node*, int>inMap;
	//入度为0的点，才能进入下面的队列
	queue<node*>zeroin;
	//把图g的所有点的入度放入inMap中。同时把入度为0的点放入zeroinQueue中
	for (auto& pair : g->nodes) {
		node* cur = pair.second;
		int initIn = cur->getIn();
		inMap[cur] = initIn;
		if (initIn == 0) {
			zeroin.push(cur);
		}
	}
	//拓扑排序的结果依次加入res数组
	vector<node*>res;
	//每次处理入度为0的点，并把和它所有相连的点的入度-1
	while (!zeroin.empty()) {
		node* cur = zeroin.front();
		zeroin.pop();
		res.push_back(cur);
		for (node* n : cur->getNext()) {
			//把cur的相邻节点入度-1
			inMap[n]--;
			if (n->getIn() == 0) {
				zeroin.push(n);
			}
		}
	}
	return res;
}
unordered_map<node*, int> graph::dijkstra(node* head) {
	//key:从head结点到该节点 
	//value:从head出发到key的最小距离
	//如果在表中，T没有被记录，那么就记head到T的距离为正无穷
	unordered_map<node*, int>distanceMap;
	//记录被选过的结点,已经求过距离的结点，以后再也不碰
	unordered_set<node*>selectedNodes;
	//把head结点先加入distanceMap中去
	distanceMap[head] = 0;
	node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);

	while (minNode) {
		int distance = distanceMap[minNode];
		for (const auto& e : minNode->getEdges()) {
			node* toNode = e->getTo();
			// 情况1：toNode未被记录 → 直接赋值
			if (distanceMap.find(toNode) == distanceMap.end()) {
				distanceMap[toNode] = distance + e->getWeight();
			}
			// 情况2：toNode已记录 → 取最小值更新
			distanceMap[toNode] = min(distanceMap[toNode], distance + e->getWeight());
		}
		selectedNodes.insert(minNode); // 标记为已确定最短路径
		minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);// 找下一个最小距离节点
	}
	return distanceMap;
}
node* graph::getMinDistanceAndUnselectedNode(
	unordered_map<node*, int>&distanceMap, 
	unordered_set<node*>&selectedNodes) 
{
	int mindistance = INT_MAX;
	node* minNode = nullptr;
	for (const auto& pair : distanceMap) {
		node* n = pair.first;
		int distance = pair.second;
		if (selectedNodes.find(n) == selectedNodes.end() && distance < mindistance) {
			minNode = n;
			mindistance = distance;
		}
	}
	return minNode;
}
//矩阵转化为我的数据结构
void graph::convertAdjMatrixToGraph(const std::vector<std::vector<int>>& adjMatrix) {
	int node_count = adjMatrix.size();
	if (node_count == 0)return;

	for (int fromnode = 0; fromnode < node_count; fromnode++) {
		for (int tonode = 0; tonode < node_count; tonode++) {
			int weight = adjMatrix[fromnode][tonode];
			if (weight == INT_MAX)//此处约定正无穷为无边的情况
			{
				continue;
			}
			//矩阵索引
			int fromval = fromnode + 1;
			int toval = tonode + 1;
			addEdge(fromval, toval, weight);
		}
	}
}
struct EdgeCompare {
	bool operator()(const edge* a, const edge* b) const {
		return a->getWeight() > b->getWeight(); // 大根堆反向定义，实现小根堆
	}
};

set<edge*> graph::primMST() {
	set<edge*> result;          // 存储最小生成树的边
	unordered_set<node*> visited; // 记录已加入生成树的节点
	priority_queue<edge*, vector<edge*>, EdgeCompare> minHeap; // 小根堆（解锁的边）

	// 遍历所有节点（处理非连通图的情况）
	for (const auto& pair : nodes) {
		node* startNode = pair.second;
		if (visited.find(startNode) != visited.end()) {
			continue; // 该节点已在生成树中，跳过
		}

		// 1. 初始化：从当前节点开始，解锁其所有边
		visited.insert(startNode);
		for (edge* e : startNode->getEdges()) {
			minHeap.push(e);
		}

		// 2. 处理小根堆中的边
		while (!minHeap.empty()) {
			edge* currEdge = minHeap.top(); // 取出权值最小的边
			minHeap.pop();

			node* toNode = currEdge->getTo();
			if (visited.find(toNode) != visited.end()) {
				continue; // 终点已在生成树中，跳过（避免环）
			}

			// 3. 该边是有效边，加入生成树
			result.insert(currEdge);
			visited.insert(toNode);

			// 4. 解锁新节点的所有边
			for (edge* nextEdge : toNode->getEdges()) {
				minHeap.push(nextEdge);
			}
		}
	}

	// 验证：生成树的边数是否符合（连通图时，边数=节点数-1）
	if (result.size() != nodes.size() - 1 && !nodes.empty()) {
		cout << "图是非连通图，生成的是最小生成森林！" << endl;
	}

	return result;
}
