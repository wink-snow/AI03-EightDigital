import os,random

def HasSolution(state):
    num = 0  # 计算逆序对数
    for i in range(1, len(state)):
        if state[i] != '0':
            for j in range(0, i):
                if state[i] < state[j] and state[j] != '0':
                    num += 1
    return num % 2 == 0  # 判断奇偶性

state="012345678"
state_list=[]
def generate_random_state():
    global state
    tmp=[]
    for i in range(0, len(state)):
        tmp.append(state[i])
    random.shuffle(tmp)
    my_string=''.join(tmp)
    if HasSolution(my_string):
        return my_string
    else:
        return generate_random_state()

def write_random_state(num):
    global state_list
    for i in range(0, num):
        state=generate_random_state()
        if state not in state_list:
            state_list.append(state)
        else:
            i=i-1
    with open(f'./random_state.list','w',encoding='utf-8') as s:
        for i in range(0, len(state_list)):
            s.write(state_list[i]+'\n')

num=int(input('请输入生成随机状态的个数：'))
write_random_state(num)