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

/*���½ṹ����ʵ����������أ�����ʵ����С���ȶ���*/
struct Cmp {
	bool operator()(pair<string, int>& a, pair<string, int>& b) {
		return a.second > b.second;
	}
};

/*EightDigital�����A*�㷨��DFS��BFS,˫��BFS,ʵ�ְ���������*/
class EightDigital
{
public:
	EightDigital(string state);/*���캯��������״̬��Ϊ��ʼ״̬*/
	void setInitialState(string state);/*���ó�ʼ״̬*/
	void setTargetState(string state);/*ע��DFS����Ϊ"176240583"����Ȼ�����ᱬը*/
	string getInitialState();/*��ȡ��ʼ״̬*/
	string getTargetState();/*��ȡĿ��״̬*/
	void PrintStringAsMatrix(string state);/*��״̬���ַ���ת����3x3�������*/
	bool HasSolution(string state);/*�жϳ�ʼ״̬�Ƿ�ɴ�*/
	void DFS(string state);/*DFS��������*/
	void BFS(string state);/*BFS��������*/
	void TwoWayBFS(string state);/*˫��BFS��������*/
	void Astar(string state);/*A*�㷨*/
	int Inspire(string state);/*A*��������,�����پ���*/
	void TryToMove(string state, char direction, int depth);/*A*״̬�ƶ�����*/
	void PrintAstarPath();/*��ӡA*�㷨·��*/
	void PrintDFSAndBFSPath();/*��ӡDFS��BFS�㷨·��*/
	void PrintTwoWayPath();/*��ӡ˫��BFS�㷨·��*/
	void Clear();/*���������ԣ�����ÿ�ε��������㷨ǰ���ô˺���*/
private:
	string initial_state_;/*�������ʼ״̬*/
	string target_state_ = "012345678";/*������Ŀ��״̬*/
	char direction[4] = { 'l','r','u','d' };/*�ƶ�����*/
	int move_direction[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };/*�ƶ������Ӧ��ά����ı仯*/
	int steps_ = 0;/*�����ڼ�¼������״̬����ע�ⲻ���ƶ�·����*/
	priority_queue<pair<string, int>, vector<pair<string, int>>, Cmp>open_;/*open��--��С���ȶ���*/
	map<string, int>closed_;/*closed��---��ϣ��*/
	map<string, int> map_depth_;/*��ȱ�ȫ�֣�*/
	map<string, string>map_path_;/*A*�㷨���ӹ�ϵ������-->����*/
	vector<string> path_;/*A*�㷨·���ϵĸ���״̬�����ã�*/
	vector<char> move_path_;/*A*�㷨·���ϵ��ƶ����򣨵��ã�*/
	map<string, int>visited_;/*���ڳ�A*�㷨���ȫ�ַ��ʼ�¼*/
	map<string, string>link_;/*���ڳ�A*�㷨��ĸ��ӹ�ϵ������--->����*/
	string key_str_;/*���ڼ�¼˫��BFS�Ĺ������ʽڵ㣬����Ϊ�ؼ��ڵ�*/
};

