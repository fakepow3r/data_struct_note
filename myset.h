#pragma once
#include"graph.h"
#include<unordered_map>
#include<vector>
class myset
{
public:
	std::unordered_map < node*, std::vector<node*>>setMap;
	//构造函数：把每个结点各自放入一个集合
	myset(std:: vector<node*>nodes) {
		for (auto& n : nodes) {
			std::vector<node*>set;
			set.push_back(n);
			setMap[n] = set;
		}
	}
	//判断集合是否相等
	bool issameset(node* from, node* to) {
		return setMap[from] == setMap[to];
	}
	//合并函数：
	void union_set(node* from, node* to) {
		std::vector<node*>fromset = setMap[from];
		std::vector<node*>toset = setMap[to];
		for (auto& n : toset) {
			fromset.push_back(n);
			setMap[n] = fromset;
		}
	}
};

