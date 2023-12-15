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
	int num = 0;/*计算逆序对数*/
	for (int i = 1; i < state.size(); ++i) {
		if (state[i] != '0') {
			for (int j = 0; j < i; ++j) {
				if (state.at(i) < state.at(j) && state[j != '0']) {
					++num;
				}
			}
		}
	}
	return num % 2 == 0;/*判断奇偶性*/
}

void EightDigital::DFS(string state) {
	visited_[state] = 1;/*进入DFS()的节点肯定没访问过，故现在标记为访问过*/
	if (visited_.find(target_state_) != visited_.end()) return;/*判断目标状态有没有访问过，访问过直接退出*/
	int curx, cury, nextx, nexty, cur_index, next_index;
	cur_index = state.find('0');
	curx = cur_index % 3;
	cury = cur_index / 3;
	for (int i = 0; i < 4; ++i) {
		string str = state;
		nextx = curx + move_direction[i][0];
		nexty = cury + move_direction[i][1];
		if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
			next_index = nextx + nexty * 3;
			str[cur_index] = str[next_index];
			str[next_index] = '0';
			if (visited_.find(str) != visited_.end())continue;/*如果节点已经访问过，直接跳出当前循环*/
			link_[str] = state;/*建立父子关系*/
			DFS(str);/*递归调用DFS*/
		}
	}
}

void EightDigital::BFS(string state) {
	queue<string>queue;
	queue.push(state);
	visited_[state] = 1;
	while (!queue.empty()) {
		string str = queue.front();/*取对头*/
		if (str == target_state_)return;/*当前队头为目标状态，直接退出函数*/
		int curx, cury, nextx, nexty, cur_index, next_index;
		cur_index = str.find('0');
		curx = cur_index % 3;
		cury = cur_index / 3;
		for (int i = 0; i < 4; ++i) {
			str = queue.front();/*每次循环str都要重新被队头赋值，否则str会发生改变*/
			nextx = curx + move_direction[i][0];
			nexty = cury + move_direction[i][1];
			if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
				next_index = nextx + nexty * 3;
				str[cur_index] = str[next_index];
				str[next_index] = '0';
				if (visited_.find(str) == visited_.end()) {/*str未被访问过，才会给它入队列*/
					link_[str] = queue.front();/*建立父子关系*/
					queue.push(str);
					visited_[str] = 1;/*标记为已访问过*/
				}
			}
		}
		queue.pop();/*与队头相关的节点都已处理完，将队头出队*/
	}
}

void EightDigital::TwoWayBFS(string state) {
	queue<string>queue[2];/*设置两个队列，分别对应从初始状态（记为d方向）,从目标状态（记为u方向）*/
	queue[0].push(initial_state_);
	queue[1].push(target_state_);
	visited_[initial_state_] = 0;/*d方向访问标记设为0*/
	visited_[target_state_] = 1;/*u方向访问标记设为1*/
	/*设置标记不同用来区分是哪个方向访问的*/
	while (!queue[0].empty() && !queue[1].empty()) {
		string str, temp_str;
		int curx, cury, nextx, nexty, cur_index, next_index;
		for (int i = 0; i < 2; ++i) {/*对应两个方向的队列*/
			str = queue[i].front();
			cur_index = str.find('0');
			curx = cur_index % 3;
			cury = cur_index / 3;
			for (int j = 0; j < 4; ++j) {/*对应四个方向*/
				temp_str = str;
				nextx = curx + move_direction[j][0];
				nexty = cury + move_direction[j][1];
				if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
					next_index = nextx + nexty * 3;
					temp_str[cur_index] = temp_str[next_index];
					temp_str[next_index] = '0';
					if (visited_.find(temp_str) == visited_.end()) {/*该状态从未被访问过(包括两个方向)*/
						queue[i].push(temp_str);
						visited_[temp_str] = i;/*做对应的标记*/
						link_[temp_str] = str;/*建立父子关系*/
					}
					else if (visited_[temp_str] ^ i) {/*该状态被其中一个方向访问过,此时的节点就是公共访问节点*/
						key_str_ = temp_str;/*记录关键节点*/
						/*此时temp_str已在关系表中，再次压入需要做方向标记防止覆盖*/
						if (i == 0)link_[temp_str + 'd'] = str;
						else link_[temp_str + 'u'] = str;
						return;/*前后搜索重合，关键节点已记录，退出函数*/
					}
				}
			}
			queue[i].pop();/*与当前队列有关节点已处理完，将当前队头出队列*/
		}
	}
}

void EightDigital::Astar(string state) {
	pair<string, int>top_pair;/*open表元素类型是pair,string表示状态，int表示f值*/
	open_.push(make_pair(state, Inspire(state)));/*初始状态深度为0*/
	map_depth_.insert(make_pair(state, 0));
	initial_state_ = state;
	while (!open_.empty()) {
		while (closed_.find(open_.top().first) != closed_.end()) {
			open_.pop();
		}/*判断当前队头是否在closed表，若在表中就出队*/
		if (open_.top().first == target_state_) return;/*当前队头是目标状态，直接退出函数*/
		top_pair = open_.top();/*临时变量赋值为队头*/
		open_.pop();/*队头出队*/
		closed_.insert(top_pair);/*队头入closed表*/
		for (int i = 0; i < 4; ++i) {/*对左右上下四个方向分别尝试移动*/
			TryToMove(top_pair.first, direction[i], map_depth_[top_pair.first] + 1);
		}
		/*由于open表是优先队列，所以只需将状态压入open表，队头自然就是值最小的节点*/
	}
}

int EightDigital::Inspire(string state) {
	int cost = 0;/*记录代价，曼哈顿距离*/
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
	/*这里没有采用move_deirection[4][2]来表示移动方向对应二维坐标的变化*/
	nextx = curx;
	nexty = cury;
	if (direction == 'l') nextx = curx - 1;
	else if (direction == 'r') nextx = curx + 1;
	else if (direction == 'u') nexty = cury - 1;
	else nexty = cury + 1;
	if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
		s[cury * 3 + curx] = s[nexty * 3 + nextx];
		s[nexty * 3 + nextx] = '0';
		if (map_depth_.find(s) == map_depth_.end()) {/*当前节点不在深度表中，以前从未被访问过*/
			map_depth_[s] = depth;/*将节点加入深度表*/
			map_path_[s] = state;/*建立父子关系*/
			open_.push(make_pair(s, depth + Inspire(s)));/*将深度+曼哈顿值得到f值，将状态压入open表*/
		}
		else {/*当前节点在深度表中，说明以前已被访问过*/
			if (depth < map_depth_[s]) {/*当前深度小于深度表中对应深度，则说明深度表需要更新*/
				map_depth_[s] = depth;
				map_path_[s] = state;
				if (closed_.find(s) != closed_.end()) {
					/*判断节点是否在closed表，若在将其移出closed表，将更新后的状态加入open表*/
					closed_.erase(s);
					open_.push(make_pair(s, depth + Inspire(s)));
				}
			}
		}
	}
}

void EightDigital::PrintAstarPath() {
	string s = target_state_;
	int move;/*用来表示前后状态的差值*/
	while (s != initial_state_) {
		move = s.find('0') - map_path_[s].find('0');
		if (move == -1)move_path_.push_back('l');
		else if (move == 1)move_path_.push_back('r');
		else if (move == -3)move_path_.push_back('u');
		else move_path_.push_back('d');
		path_.push_back(s);
		s = map_path_[s];
	}
	path_.push_back(initial_state_);
	/*由于此时path里面的路径是倒置的，故将其反向输出，也可以用栈实现，但输出结束栈空，路径无法保留*/
	for (int i = 0; i < path_.size(); ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << path_[path_.size() - 1 - i][j] << '\t';
			if ((j + 1) % 3 == 0 && j > 0)cout << endl;
		}
		cout << "******************" << endl;
	}
	cout << "MovePath->";
	for (int i = move_path_.size() - 1; i >= 0; --i)cout << move_path_[i];
	cout << endl;
}

void EightDigital::PrintDFSAndBFSPath() {
	stack<string> stack;
	string str = target_state_;
	while (str != initial_state_) {
		stack.push(str);
		str = link_[str];/*自下而上查找，直到找到初始状态*/
	}
	stack.push(initial_state_);
	int num = stack.size();/*记录步数*/
	while (!stack.empty()) {
		PrintStringAsMatrix(stack.top());
		stack.pop();
	}
	cout << "共" << num << "步." << endl;
}

void EightDigital::PrintTwoWayPath() {
	string str;
	/*由于双向BFS,所以利用关键节点key_str，从两个方向反向搜索*/
	if (link_.find(key_str_ + 'd') != link_.end()) {/*关键节点是d方向后找到的*/
		str = link_[key_str_ + 'd'];
		stack<string> prec_stack;
		while (str != initial_state_) {
			prec_stack.push(str);
			str = link_[str];
		}
		prec_stack.push(initial_state_);
		while (!prec_stack.empty()) {
			PrintStringAsMatrix(prec_stack.top());
			prec_stack.pop();
		}
		str = link_[key_str_];
		while (str != target_state_) {
			PrintStringAsMatrix(str);
			str = link_[str];
		}
		PrintStringAsMatrix(target_state_);
	}
	else {/*关键节点是u方向后找到的*/
		str = key_str_;
		stack<string> prec_stack;
		while (str != initial_state_) {
			prec_stack.push(str);
			str = link_[str];
		}
		prec_stack.push(initial_state_);
		while (!prec_stack.empty()) {
			PrintStringAsMatrix(prec_stack.top());
			prec_stack.pop();
		}
		str = link_[key_str_ + 'u'];
		while (str != target_state_) {
			PrintStringAsMatrix(str);
			str = link_[str];
		}
		PrintStringAsMatrix(target_state_);
	}
}

void EightDigital::Clear() {
	/*清空相关属性，防止前一次调用相关属性会发生变化，建议每次调用搜索算法前调用此函数*/
	steps_ = 0;
	while (!open_.empty())open_.pop();
	closed_.clear();
	map_depth_.clear();
	map_path_.clear();
	path_.clear();
	move_path_.clear();
	visited_.clear();
	link_.clear();
	key_str_ = "";
}