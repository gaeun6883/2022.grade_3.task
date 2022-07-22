#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

vector<int> order;
vector<int> frame;
int s, frame_num;

int sol_optimal(int position, int c);
int isExist(int target);
bool findQueue(queue<int> q, int x);

void optimal();
void LRU();
void ESCA();
void print_memory();
void print_ESCA(queue<int> q, vector<int> v);
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << "\n페이지 아이디(숫자)를 입력해주세요(음수 넣을 시 종료): ";
	while (true) {
		int num;
		cin >> num;
		if (num < 0) break;
		order.push_back(num);
	}
	cout << "\n프레임 개수 입력: ";
	cin >> frame_num;
	s = order.size();

	optimal();
	LRU();
	ESCA();

	system("pause");
	return 0;
}

void optimal() {
	cout << "optimal algorithm________________\n";
	int cur = 0, hit_cnt=0, fault_cnt = 0;
	int outpage = 0, tmp = 0;
	frame.clear();
	frame.resize(frame_num);

	for (int i = 0; i < s; i++) {
		outpage = 0;
		if (cur < frame_num) {
			if (isExist(order[i]) == -1) {
				frame[cur] = order[i];
				fault_cnt++;
				cur++;
			}
			else continue;
		}
		else {
			if (isExist(order[i]) != -1) {
				hit_cnt++;
				continue;
			}
			for (int j = 0; j < frame_num; j++) {
				if (outpage < sol_optimal(i, frame[j])) {
					outpage = sol_optimal(i, frame[j]);
					tmp = j;
				}
			}
			frame[tmp] = order[i];
			fault_cnt++;
		}
		print_memory();
	}
	cout << "Hits: " << hit_cnt << "\nFaults: " << fault_cnt << '\n';
	cout << "Fault Rate: " << (fault_cnt * 1.0) / (s * 1.0) << "\n";
}

void LRU() {
	cout << "LRU algorithm________________\n";
	int tmp, hit_cnt=0, fault_cnt = 0;
	int cur, cursize = 0;
	frame.clear();
	frame.resize(frame_num);

	for (int i = 0; i < s; i++){
		if ((cur = isExist(order[i])) != -1){
			tmp = frame[cur];
			for (int j = cur; j < cursize - 1; j++)
				frame[j] = frame[j + 1];

			frame[cursize - 1] = tmp;
			hit_cnt++;
		}
		else {//page fault
			if (frame_num == cursize) {
				for (int j = 1; j < frame_num; j++)
					frame[j - 1] = frame[j];

				frame[frame_num - 1] = order[i];
			}
			else {
				frame[cursize] = order[i];
				cursize++;
			}
			fault_cnt++;
		}
		print_memory();
	}
	cout << "Hits: " << hit_cnt << "\nFaults: " << fault_cnt << '\n';
	cout << "Fault Rate: " << (fault_cnt * 1.0) / (s * 1.0) << "\n";
}

void  ESCA() {
	cout << "Enhanced Second Chance algorithm________________\n";
	queue<int> q;
	vector<int> ref_bit;
	ref_bit.resize(frame_num);
	int hit_cnt = 0, fault_cnt = 0;

	int ptr = 0;
	int count = 0;
	for (int i = 0; i < s; i++) {
		if (!findQueue(q, order[i])) {
			if (count < frame_num) {
				q.push(order[i]);
				count++;
			}
			else {
				ptr = 0;
				while (!q.empty()) {
					if (ref_bit[ptr % frame_num]) {
						ref_bit[ptr % frame_num] = !ref_bit[ptr % frame_num];
					}
					else break;
					ptr++;
				}
				if (q.empty()) {
					q.pop();
					q.push(order[i]);
				}
				else {
					int j = 0;
					while (j < (ptr % frame_num)) {
						int t1 = q.front();
						q.pop();
						q.push(t1);
						bool temp = frame[0];
						for (int counter = 0; counter < frame_num - 1; counter++)
							ref_bit[counter] = ref_bit[counter + 1];
						ref_bit[frame_num - 1] = temp;
						j++;
					}
					q.pop();
					q.push(order[i]);
				}
			}
			fault_cnt++;
		}
		else {
			queue<int> temp = q;
			int counter = 0;
			while (!q.empty()) {
				if (q.front() == order[i])
					ref_bit[counter] = 1;
				counter++;
				q.pop();
			}
			q = temp;
			hit_cnt++;
		}
		print_ESCA(q, ref_bit);
	}
	cout << "Hits: " << hit_cnt << "\nFaults: " << fault_cnt << '\n';
	cout << "Fault Rate: " << (fault_cnt * 1.0) / (s * 1.0) << "\n";
}

void print_memory() {
	printf("Memory Status : ");
	for (int i = 0; i < frame_num; i++)
		printf("%d ", frame[i]);
	printf("\n");
}
void print_ESCA(queue<int> q, vector<int> bit) {
	vector<int> print;
	print.resize(frame_num);
	queue<int> tmp;
	tmp = q;
	int size = q.size();
	for (int i = size - 1; i >= 0; i--) {
		int num = q.front();
		q.pop();
		print[i] = num;
	}

	printf("Memory Status        : ");
	for (int i = 0; i < frame_num; i++)
		printf("%d ", print[i]);
	cout << "\n";
	printf("reference bit Status : ");
	for (int i = 0; i < frame_num; i++)
		printf("%d ", bit[i]);
	cout << "\n\n";

	q = tmp;
}

int sol_optimal(int position, int c) {
	int dist = 0;
	for (int i = position + 1; i < s; i++)
		if (order[i] != c) dist++;
		else break;
	return dist + 1;
}
int isExist(int target) {
	int i;
	for (i = 0; i < frame_num; i++)
		if (frame[i] == target)
			return i;
	return -1;
}
bool findQueue(queue<int> q, int x){
	while (!q.empty()) {
		if (x == q.front())
			return true;
		q.pop();
	}
	return false;
}