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
	int num = 0;/*�����������*/
	for (int i = 1; i < state.size(); ++i) {
		if (state[i] != '0') {
			for (int j = 0; j < i; ++j) {
				if (state.at(i) < state.at(j) && state[j != '0']) {
					++num;
				}
			}
		}
	}
	return num % 2 == 0;/*�ж���ż��*/
}

void EightDigital::DFS(string state) {
	visited_[state] = 1;/*����DFS()�Ľڵ�϶�û���ʹ��������ڱ��Ϊ���ʹ�*/
	if (visited_.find(target_state_) != visited_.end()) return;/*�ж�Ŀ��״̬��û�з��ʹ������ʹ�ֱ���˳�*/
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
			if (visited_.find(str) != visited_.end())continue;/*����ڵ��Ѿ����ʹ���ֱ��������ǰѭ��*/
			link_[str] = state;/*�������ӹ�ϵ*/
			DFS(str);/*�ݹ����DFS*/
		}
	}
}

void EightDigital::BFS(string state) {
	queue<string>queue;
	queue.push(state);
	visited_[state] = 1;
	while (!queue.empty()) {
		string str = queue.front();/*ȡ��ͷ*/
		if (str == target_state_)return;/*��ǰ��ͷΪĿ��״̬��ֱ���˳�����*/
		int curx, cury, nextx, nexty, cur_index, next_index;
		cur_index = str.find('0');
		curx = cur_index % 3;
		cury = cur_index / 3;
		for (int i = 0; i < 4; ++i) {
			str = queue.front();/*ÿ��ѭ��str��Ҫ���±���ͷ��ֵ������str�ᷢ���ı�*/
			nextx = curx + move_direction[i][0];
			nexty = cury + move_direction[i][1];
			if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
				next_index = nextx + nexty * 3;
				str[cur_index] = str[next_index];
				str[next_index] = '0';
				if (visited_.find(str) == visited_.end()) {/*strδ�����ʹ����Ż���������*/
					link_[str] = queue.front();/*�������ӹ�ϵ*/
					queue.push(str);
					visited_[str] = 1;/*���Ϊ�ѷ��ʹ�*/
				}
			}
		}
		queue.pop();/*���ͷ��صĽڵ㶼�Ѵ����꣬����ͷ����*/
	}
}

void EightDigital::TwoWayBFS(string state) {
	queue<string>queue[2];/*�����������У��ֱ��Ӧ�ӳ�ʼ״̬����Ϊd����,��Ŀ��״̬����Ϊu����*/
	queue[0].push(initial_state_);
	queue[1].push(target_state_);
	visited_[initial_state_] = 0;/*d������ʱ����Ϊ0*/
	visited_[target_state_] = 1;/*u������ʱ����Ϊ1*/
	/*���ñ�ǲ�ͬ�����������ĸ�������ʵ�*/
	while (!queue[0].empty() && !queue[1].empty()) {
		string str, temp_str;
		int curx, cury, nextx, nexty, cur_index, next_index;
		for (int i = 0; i < 2; ++i) {/*��Ӧ��������Ķ���*/
			str = queue[i].front();
			cur_index = str.find('0');
			curx = cur_index % 3;
			cury = cur_index / 3;
			for (int j = 0; j < 4; ++j) {/*��Ӧ�ĸ�����*/
				temp_str = str;
				nextx = curx + move_direction[j][0];
				nexty = cury + move_direction[j][1];
				if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
					next_index = nextx + nexty * 3;
					temp_str[cur_index] = temp_str[next_index];
					temp_str[next_index] = '0';
					if (visited_.find(temp_str) == visited_.end()) {/*��״̬��δ�����ʹ�(������������)*/
						queue[i].push(temp_str);
						visited_[temp_str] = i;/*����Ӧ�ı��*/
						link_[temp_str] = str;/*�������ӹ�ϵ*/
					}
					else if (visited_[temp_str] ^ i) {/*��״̬������һ��������ʹ�,��ʱ�Ľڵ���ǹ������ʽڵ�*/
						key_str_ = temp_str;/*��¼�ؼ��ڵ�*/
						/*��ʱtemp_str���ڹ�ϵ���У��ٴ�ѹ����Ҫ�������Ƿ�ֹ����*/
						if (i == 0)link_[temp_str + 'd'] = str;
						else link_[temp_str + 'u'] = str;
						return;/*ǰ�������غϣ��ؼ��ڵ��Ѽ�¼���˳�����*/
					}
				}
			}
			queue[i].pop();/*�뵱ǰ�����йؽڵ��Ѵ����꣬����ǰ��ͷ������*/
		}
	}
}

void EightDigital::Astar(string state) {
	pair<string, int>top_pair;/*open��Ԫ��������pair,string��ʾ״̬��int��ʾfֵ*/
	open_.push(make_pair(state, Inspire(state)));/*��ʼ״̬���Ϊ0*/
	map_depth_.insert(make_pair(state, 0));
	initial_state_ = state;
	while (!open_.empty()) {
		while (closed_.find(open_.top().first) != closed_.end()) {
			open_.pop();
		}/*�жϵ�ǰ��ͷ�Ƿ���closed�����ڱ��оͳ���*/
		if (open_.top().first == target_state_) return;/*��ǰ��ͷ��Ŀ��״̬��ֱ���˳�����*/
		top_pair = open_.top();/*��ʱ������ֵΪ��ͷ*/
		open_.pop();/*��ͷ����*/
		closed_.insert(top_pair);/*��ͷ��closed��*/
		for (int i = 0; i < 4; ++i) {/*�����������ĸ�����ֱ����ƶ�*/
			TryToMove(top_pair.first, direction[i], map_depth_[top_pair.first] + 1);
		}
		/*����open�������ȶ��У�����ֻ�轫״̬ѹ��open����ͷ��Ȼ����ֵ��С�Ľڵ�*/
	}
}

int EightDigital::Inspire(string state) {
	int cost = 0;/*��¼���ۣ������پ���*/
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
	/*����û�в���move_deirection[4][2]����ʾ�ƶ������Ӧ��ά����ı仯*/
	nextx = curx;
	nexty = cury;
	if (direction == 'l') nextx = curx - 1;
	else if (direction == 'r') nextx = curx + 1;
	else if (direction == 'u') nexty = cury - 1;
	else nexty = cury + 1;
	if (nextx >= 0 && nextx < 3 && nexty >= 0 && nexty < 3) {
		s[cury * 3 + curx] = s[nexty * 3 + nextx];
		s[nexty * 3 + nextx] = '0';
		if (map_depth_.find(s) == map_depth_.end()) {/*��ǰ�ڵ㲻����ȱ��У���ǰ��δ�����ʹ�*/
			map_depth_[s] = depth;/*���ڵ������ȱ�*/
			map_path_[s] = state;/*�������ӹ�ϵ*/
			open_.push(make_pair(s, depth + Inspire(s)));/*�����+������ֵ�õ�fֵ����״̬ѹ��open��*/
		}
		else {/*��ǰ�ڵ�����ȱ��У�˵����ǰ�ѱ����ʹ�*/
			if (depth < map_depth_[s]) {/*��ǰ���С����ȱ��ж�Ӧ��ȣ���˵����ȱ���Ҫ����*/
				map_depth_[s] = depth;
				map_path_[s] = state;
				if (closed_.find(s) != closed_.end()) {
					/*�жϽڵ��Ƿ���closed�����ڽ����Ƴ�closed�������º��״̬����open��*/
					closed_.erase(s);
					open_.push(make_pair(s, depth + Inspire(s)));
				}
			}
		}
	}
}

void EightDigital::PrintAstarPath() {
	string s = target_state_;
	int move;/*������ʾǰ��״̬�Ĳ�ֵ*/
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
	/*���ڴ�ʱpath�����·���ǵ��õģ��ʽ��䷴�������Ҳ������ջʵ�֣����������ջ�գ�·���޷�����*/
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
		str = link_[str];/*���¶��ϲ��ң�ֱ���ҵ���ʼ״̬*/
	}
	stack.push(initial_state_);
	int num = stack.size();/*��¼����*/
	while (!stack.empty()) {
		PrintStringAsMatrix(stack.top());
		stack.pop();
	}
	cout << "��" << num << "��." << endl;
}

void EightDigital::PrintTwoWayPath() {
	string str;
	/*����˫��BFS,�������ùؼ��ڵ�key_str������������������*/
	if (link_.find(key_str_ + 'd') != link_.end()) {/*�ؼ��ڵ���d������ҵ���*/
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
	else {/*�ؼ��ڵ���u������ҵ���*/
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
	/*���������ԣ���ֹǰһ�ε���������Իᷢ���仯������ÿ�ε��������㷨ǰ���ô˺���*/
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