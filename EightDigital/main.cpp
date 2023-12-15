// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"EightDigital.h"

int main() {
	string str = "724506831";/*初始化初始状态*/
	EightDigital e1(str);/*A*算法*/
	EightDigital e2(str);/*双向BFS*/
	EightDigital e3(str);/*BFS*/
	EightDigital e4(str);/*DFS*/
	EightDigital e5(str);/*DFS*/
	if (e1.HasSolution(e1.getInitialState())) {
		e1.Astar(e1.getInitialState());
		cout << "****** Astar *********" << endl;
		e1.PrintAstarPath();
	}
	system("pause");

	if (e2.HasSolution(e2.getInitialState())) {
		e2.Clear();
		e2.TwoWayBFS(e2.getInitialState());
		cout << "****** TwoWayBFS *********" << endl;
		e2.PrintTwoWayPath();
	}
	system("pause");

	if (e3.HasSolution(e3.getInitialState())) {
		e3.Clear();
		e3.BFS(e3.getInitialState());
		cout << "****** BFS *********" << endl;
		e3.PrintDFSAndBFSPath();
	}
	system("pause");

	e4.Clear();
	e4.setTargetState("602741583");
	e4.DFS(e4.getInitialState());
	cout << "****** DFS *********" << endl;
	e4.PrintDFSAndBFSPath();
	/*因为DFS采用递归或栈实现，由于移动方向比较多。所以如果步数较多，那么空间爆炸将会停止搜索，*/
	/*经测试，VS最多可搜索1000左右，VSCode可搜索10000左右，所以e4修改了目标状态，*/
	/*而e5则是将初始状态变得很简单(离目标状态很近)，所以八数码问题不建议采用单纯DFS*/
	if (e5.HasSolution(e5.getInitialState())) {
		e5.Clear();
		e5.setInitialState("312405678");
		e5.DFS(e5.getInitialState());
		cout << "****** DFS *********" << endl;
		e5.PrintDFSAndBFSPath();
	}
	/*总之，算法快慢比较Astar>TwoWayBFS>BFS>DFS,前两种比较实用,运行时后两者可能会很慢*/
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
