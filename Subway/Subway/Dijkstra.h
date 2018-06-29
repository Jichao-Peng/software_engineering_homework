//Created by 王希 娄宁
#pragma once


#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define INT_MAX 10000000
/*
本程序是使用Dijkstra算法实现求解最短路径的问题
采用的邻接矩阵来存储图
*/
//记录起点到每个顶点的最短路径的信息
template<class T>
int length(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}

struct Dis {
	string path;
	double value;
	bool visit;
	Dis() {
		visit = false;
		value = 0;
		path = "";
	}
};

class Graph_DG {
public:
	int vexnum;   //图的顶点个数
	int edge;     //图的边数
	double **arc;   //邻接矩阵
	Dis * dis;   //记录各个顶点最短路径的信息
	vector<string> StationName;
	vector<vector<int>>IndexRoute;
	string returnpath;
	vector<int> returnindex;
public:
	//构造函数
	Graph_DG(int vexnum,int edge);
	Graph_DG(int vexnum);
	//析构函数
	~Graph_DG();
	// 判断我们每次输入的的边的信息是否合法
	//顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph();
	//打印邻接矩阵
	void print();
	//求最短路径
	void Dijkstra(int begin);
	void Dijkstra(string, string end, string& a, vector<int>& returnindex);
	//打印最短路径
	void print_path(int);
	string print_path(string, string);
	int WhichStation(string);
	string WhichLine(int);
	bool ReadFile(const string& File);
	vector<int> Search_Same_Station(string name,const vector<string>&StationName);
	string ReturnString(int);
	//string ReturnRoute(string, string);
	vector<int>& ReturnIndex(string, string);
	void reset();
};
