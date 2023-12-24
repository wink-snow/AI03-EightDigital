#include "EightDigital.h"
#include<fstream>

int main()
{
    cout << "********* EightDigital *********" << endl;
    ifstream file("./test/random_state.list");

    if(!file)
    {
        cout << "open file failed" << endl;
        return 0;
    }
    string line;
    int lines=0;
    while(getline(file, line))
    {
        lines++;
    }
    file.close();
    cout << "检测到 " << lines << " 组测试样例" << endl;
    system("pause");
    cout <<"测试开始......"<<endl;
    
    ifstream f("./test/random_state.list");

    if(!f)
    {
        cout << "open file failed" << endl;
        return 0;
    }
    lines=0;
    while(getline(f, line))
    {
        lines++;
        EightDigital e1(line);
        e1.Clear();
        if (e1.HasSolution(e1.getInitialState())) {
		    e1.Astar(e1.getInitialState());
		    e1.PrintAstarPath();
	    }
        cout << "****** 样例 " << lines <<" 测试完成 *********" << endl;
        if(lines<10)
        {
            cout << "****** 样例 " << lines+1 <<" 准备中 *********" << endl;
        }
        f.clear();
        system("pause");
    }
    f.close();
    cout << "****** 所有样例测试完成，准备退出...... *********" << endl;

    system("pause");
    return 0;
}