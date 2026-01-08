#pragma once
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include"node.h"
#include"edge.h"
#include<vector>
#include<queue>
#include <set>
class graph
{
public:
    std::unordered_map<int, node*>nodes;
    std::unordered_set<edge*>edges;
    graph() :nodes(), edges() {}
    ~graph() {
        for (auto& pair : nodes) {
            delete pair.second;
        }
        for (auto e : edges) {
            delete e;
        }
    }
    //添加节点
    void addNode(int val) {
        if (nodes.find(val) == nodes.end()) {
            nodes[val] = new node(val);
        }
    }
    //添加边
    void addEdge(int fromVal, int inVal, int w)//w为权重
    {
        addNode(fromVal);
        addNode(inVal);
        node* from = nodes[fromVal];
        node* to = nodes[inVal];
        edge* e = new edge(w, from, to);

        edges.insert(e);
    }
	void bfs(node*n);//广度优先遍历
    void dfs(node* n);//深度优先遍历
    std::vector<node*> sortedtopology(graph* g);
    node* prime();//最小生成树prime算法,
    //学习并查集
    // 邻接矩阵转自定义图结构（nodeVal从1开始，无边标记为-1）
    void convertAdjMatrixToGraph(const std::vector<std::vector<int>>& adjMatrix);
    std::unordered_map<node*,int> dijkstra(node*head);//最短路径。不允许有累加和为负数的环
    node* getMinDistanceAndUnselectedNode(unordered_map<node*,int>&distanceMap, unordered_set<node*>&selectedNodes);
    set<edge*> primMST(); // 返回最小生成树的边集合
};

