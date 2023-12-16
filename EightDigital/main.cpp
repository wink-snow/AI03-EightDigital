#include"EightDigital.h"

int main() {
	cout << "********* EightDigital *********" << endl;
	cout << "请初始化初始状态：" << endl;
	string str = "";//724506831
	getline(cin, str);
	EightDigital e1(str);//A*算法

	if (e1.HasSolution(e1.getInitialState())) {
		e1.Astar(e1.getInitialState());
		cout << "****** Astar *********" << endl;
		e1.PrintAstarPath();
	}
	system("pause");

	return 0;
}
