#include "EightDigital.h"
EightDigital::EightDigital(string initial_state) {
	initial_state_ = initial_state;
}

void EightDigital::setInitialState(string state) {
	initial_state_ = state;
}

void EightDigital::setTargetState(string state) {
	target_state_ = state;
}

string EightDigital::getInitialState() {
	return initial_state_;
}

string EightDigital::getTargetState() {
	return target_state_;
}

void EightDigital::PrintStringAsMatrix(string state) {
	for (int i = 0; i < 9; ++i) {
		cout << state[i] << '\t';
		if ((i + 1) % 3 == 0)cout << endl;
	}
	cout << "******************" << endl;
}

bool EightDigital::HasSolution(string state) {
	int num = 0;//计算逆序对数 
	for (int i = 1; i < int(state.size()); ++i) {
		if (state[i] != '0') {
			for (int j = 0; j < i; ++j) {
				if (state.at(i) < state.at(j) && state[j != '0']) {
					++num;
				}
			}
		}
	}
	return num % 2 == 0;//判断奇偶性 
}

void EightDigital::Astar(string state) {
	pair<string, int>top_pair;//open表元素类型是pair,string表示状态，int表示f值 
	open_.push(make_pair(state, Inspire(state)));//初始状态深度为0 
	map_depth_.insert(make_pair(state, 0));
	initial_state_ = state;
	while (!open_.empty()) {
		while (closed_.find(open_.top().first) != closed_.end()) {
			open_.pop();
		}//判断当前队头是否在closed表，若在表中就出队 
		if (open_.top().first == target_state_) return;//当前队头是目标状态，直接退出函数 
		top_pair = open_.top();//临时变量赋值为队头 
		open_.pop();//队头出队 
		closed_.insert(top_pair);//队头入closed表 
		for (int i = 0; i < 4; ++i) {//对左右上下四个方向分别尝试移动 
			TryToMove(top_pair.first, direction[i], map_depth_[top_pair.first] + 1);
		}
		//由于open表是优先队列，所以只需将状态压入open表，队头自然就是值最小的节点 
	}
}

int EightDigital::Inspire(string state) {
	int cost = 0;//记录代价，曼哈顿距离 
	for (int i = 0; i < 9; ++i) {
		if (state[i] != '0') {
			cost += abs((state[i] - '0') / 3 - i / 3) + abs((state[i] - '0') % 3 - i % 3);
		}
	}
	return cost;
}

void EightDigital::TryToMove(string state, char direction, int depth) {
	string s = state;
	int curx, cury, nextx, nexty;
	curx = state.find('0') % 3;
	cury = state.find('0') / 3;
	//这里没有采用move_deirection[4][2]来表示移动方向对应二维坐标的变化 
	nextx = curx;
	nexty = cury;
	if (direction == 'l') nextx = curx - 1;
	else if (direction == 'r') nextx = curx + 1;
	else if (direction == 'u') nexty = cury - 1;
	else if (direction == 'd') nexty = cury + 1;
	if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
		s[cury * 3 + curx] = s[nexty * 3 + nextx];
		s[nexty * 3 + nextx] = '0';
		if (map_depth_.find(s) == map_depth_.end()) {//当前节点不在深度表中，以前从未被访问过 
			map_depth_[s] = depth;//将节点加入深度表 
			map_path_[s] = state;//建立父子关系 
			open_.push(make_pair(s, depth + Inspire(s)));//将深度+曼哈顿值得到f值，将状态压入open表 
		}
		else {//当前节点在深度表中，说明以前已被访问过 
			if (depth < map_depth_[s]) {//当前深度小于深度表中对应深度，则说明深度表需要更新 
				map_depth_[s] = depth;
				map_path_[s] = state;
				if (closed_.find(s) != closed_.end()) {
					//判断节点是否在closed表，若在将其移出closed表，将更新后的状态加入open表 
					closed_.erase(s);
					open_.push(make_pair(s, depth + Inspire(s)));
				}
			}
		}
	}
}

void EightDigital::PrintAstarPath() {
	string s = target_state_;
	int move;//用来表示前后状态的差值 
	while (s != initial_state_) {
		move = s.find('0') - map_path_[s].find('0');
		if (move == -1) move_path_.push_back('l');
		else if (move == 1) move_path_.push_back('r');
		else if (move == -3) move_path_.push_back('u');
		else if (move == 3) move_path_.push_back('d');
		path_.push_back(s);
		s = map_path_[s];
	}
	path_.push_back(initial_state_);
	for(int i = 0; i < int(path_.size()); ++i){
		PrintStringAsMatrix(path_[path_.size() - 1 - i]);
	}
	cout << "MovePath->";
	for (int i = move_path_.size() - 1; i >= 0; --i)cout << move_path_[i];
	cout << endl;
}

void EightDigital::Clear() {
	//清空相关属性，防止前一次调用相关属性会发生变化，建议每次调用搜索算法前调用此函数
	steps_ = 0;
	while (!open_.empty())open_.pop();
	closed_.clear();
	map_depth_.clear();
	map_path_.clear();
	path_.clear();
	move_path_.clear();
}