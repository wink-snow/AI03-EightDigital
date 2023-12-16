#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<functional>
//#include<vector>
#include<map>
#include<cstdlib>
#include<utility>
using namespace std;

//以下结构用于实现运算符重载，用以实现最小优先队列 
struct Cmp {
	bool operator()(pair<string, int>& a, pair<string, int>& b) {
		return a.second > b.second;
	}
};

//EightDigital类包含A*算法，实现八数码难题 
class EightDigital
{
public:
	EightDigital(string state);//构造函数，传入状态即为初始状态 
	void setInitialState(string state);//设置初始状态 
	void setTargetState(string state);//设置目标状态 
	string getInitialState();//获取初始状态 
	string getTargetState();//获取目标状态 
	void PrintStringAsMatrix(string state);//将状态由字符串转换成3x3矩阵输出 
	bool HasSolution(string state);//判断初始状态是否可达 

	void Astar(string state);//A*算法 
	int Inspire(string state);//A*启发函数,曼哈顿距离 
	void TryToMove(string state, char direction, int depth);//A*状态移动处理 
	void PrintAstarPath();//打印A*算法路径 

	void Clear();//清空相关属性，建议每次调用搜索算法前调用此函数 
private:
	string initial_state_;//八数码初始状态 
	string target_state_ = "012345678";//八数码目标状态 
	char direction[4] = { 'l','r','u','d' };//移动方向 
	int move_direction[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//移动方向对应二维坐标的变化 
	int steps_ = 0;//可用于记录搜索的状态数（注意不是移动路径） 
	priority_queue<pair<string, int>, vector<pair<string, int>>, Cmp>open_;//open表--最小优先队列 
	map<string, int>closed_;//closed表---哈希表 
	map<string, int> map_depth_;//深度表（全局） 
	map<string, string>map_path_;//A*算法父子关系表，孩子-->父亲 
	vector<string> path_;//A*算法路径上的各个状态（倒置） 
	vector<char> move_path_;//A*算法路径上的移动方向（倒置） 
	map<string, int>visited_;//用于除A*算法外的全局访问记录 
	map<string, string>link_;//用于除A*算法外的父子关系表，孩子--->父亲 
	string key_str_;//用于记录双向BFS的公共访问节点，命名为关键节点 
};

