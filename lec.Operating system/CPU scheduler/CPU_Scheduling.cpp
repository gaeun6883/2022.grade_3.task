#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

typedef struct process {
	int id = 0; // 프로세스 번호
	int arrive = 0; // 도착시간
	int exe = 0; // 실행시간
	int priority = 0; // 우선순위
}process;
vector<process> list;


typedef struct exec {
	int start;
	int end;
	int exe;
}exec;
vector<exec>* result;
vector<pair<string,exec>> seq;

vector<int> startTime;
vector<int> exeTime;
vector<int> endTime;
vector<int> waitTime;
vector<int> turnaroundTime;
vector<int> responseTime;

struct cmp_priority {
	bool operator()(process a, process b) {
		return a.priority > b.priority;
	}
};
struct cmp_exe {
	bool operator()(process a, process b) {
		return a.exe > b.exe;
	}
};
bool cmp_arrive(const process& a, const process& b) {
	return (a.arrive != b.arrive) ? (a.arrive < b.arrive) : (a.id < b.id);
}

int timeSlice, s, total=0;
void SJF();
void Priority();
void RR();
void print();

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int idx = 1;
	cout << "-arrve time이 0인 process는 반드시 한 개 이상 있어야한다.\n";
	cout << "-프로세스 입력 종료를 위해 -1 -1 -1를 입력하세요.\n";
	while (true) {
		cout << idx << "번 프로세스(arrival time, execution time, priority)입력: ";
		int a, b, c;
		cin >> a >> b >> c;
		if (a < 0 || b < 0 || c < 0) break;
		list.push_back({ idx,a,b,c });
		exeTime.push_back(b);
		total += b;
		idx++;
	}
	s = list.size();
	cout << total;

	result = new vector<exec>[s];
	startTime.resize(s);
	endTime.resize(idx);
	waitTime.resize(idx);
	turnaroundTime.resize(idx);
	responseTime.resize(s);

	cout << "\ntime slice 값 입력: ";
	cin >> timeSlice;
	
	SJF();
	Priority();
	RR();

	cout << "\n\nfinish";
	system("pause");
	return 0;
}

void SJF() {
	process cur, tmp;
	int complete = 0, turnaround = 0, wait = 0, time = 0;
	for (int i = 0; i <s; i++)
		result[i].clear();
	seq.clear();
	fill(startTime.begin(), startTime.end(), -1);

	priority_queue<process, vector<process>, cmp_exe> ready;
	sort(list.begin(), list.end(), cmp_arrive);

	queue<process> q;
	for (int i = 0; i < s; i++)
		q.push(list[i]);
	cur = q.front();
	q.pop();
	exec a;
	a.start = 0;

	while (time <= total) {//본격 스케줄링
		while (true) {
			if (!q.empty() && q.front().arrive == time) {
				tmp = q.front();
				q.pop();
				if (startTime[tmp.id - 1] == -1) startTime[tmp.id - 1] = time;
				if (tmp.exe < cur.exe) {//선점
					a.end = time;
					a.exe = time - a.start;
					if (a.exe != 0) {
						result[cur.id - 1].push_back(a);
						string s = "P" + to_string(cur.id);
						seq.push_back({ s,a });
					}
					a.start = time;
					ready.push(cur);
					cur = tmp;
				}
				else ready.push(tmp);
			}
			else break;
		}

		if (cur.exe == 0) {//처리완료
			int id = cur.id;
			int exe = cur.exe;
			int arrive = cur.arrive;

			complete = time;
			wait = complete-exeTime[id - 1]-arrive;
			turnaround = complete - arrive;
			endTime[id - 1] = complete;
			turnaroundTime[id - 1] = turnaround;
			waitTime[id - 1] = wait;
			responseTime[id-1] =exeTime[id-1]+wait;

			a.end = time;
			a.exe = time - a.start;
			if (a.exe != 0) {
				result[id - 1].push_back(a);
				string s = "P" + to_string(id);
				seq.push_back({ s,a });
			}
			a.start = time;

			if (!ready.empty()) {
				cur = ready.top();
				ready.pop();
			}
			else if (time != total && ready.empty()) {
				cout << "SJF 스케줄링 중간에 공백이 생겼습니다.";
				system("pause");
				exit(1);
			}
			else break;
		}
		cur.exe--;
		time++;
	}
	cout << "\n--------------------SJF algorithm----------------------------------------------------------------------------\n";
	print();
}
void Priority() {
	process cur, tmp;
	int complete = 0, turnaround = 0, wait = 0, time = 0;

	for (int i = 0; i < s; i++)
		result[i].clear();
	fill(startTime.begin(), startTime.end(), -1);
	seq.clear();

	priority_queue<process, vector<process>, cmp_priority> ready;
	sort(list.begin(), list.end() , cmp_arrive);

	queue<process> q;
	for (int i = 0; i < s; i++)
		q.push(list[i]);
	cur = q.front();
	q.pop();
	exec a;
	a.start = 0;

	while (time <= total) {
		while (1) {
			if (q.size() != 0 && q.front().arrive == time) {
				tmp = q.front();
				q.pop();
				if (startTime[tmp.id - 1] == -1) startTime[tmp.id - 1] = time;
				if (tmp.priority < cur.priority) {
					a.end = time;
					a.exe = time - a.start;
					if (a.exe != 0) {
						result[list.size() - 1].push_back(a);
						string s = "P" + to_string(cur.id);
						seq.push_back({ s,a });
					}
					a.start = time;
					ready.push(cur);
					cur = tmp;
				}
				else
					ready.push(tmp);
			}
			else break;
		}

		if (cur.exe == 0) {

			int id = cur.id;
			int exe = cur.exe;
			int arrive = cur.arrive;

			complete = time;
			wait = complete - exeTime[id - 1] - arrive;
			turnaround = complete - arrive;
			endTime[id - 1] = complete;
			turnaroundTime[id - 1] = turnaround;
			waitTime[id - 1] = wait;
			responseTime[id - 1] = exeTime[id - 1] + wait;

			a.end = time;
			a.exe = time - a.start;
			if (a.exe != 0) {
				result[id - 1].push_back(a);
				string s = "P" + to_string(cur.id);
				seq.push_back({ s,a });
			}
			a.start = time;

			if (!ready.empty()) {
				cur = ready.top();
				ready.pop();
			}

			else if (time != total && ready.empty()) {
				cout << "Priority 스케줄링 중간에 공백이 생겼습니다. - 잘못된 입력입니다.";
				system("pause");
				exit(1);
			}
			else break;
		}

		cur.exe--;
		time++;
	}

	cout << "\n--------------Priority algorithm---------------------------------------------------------------------------\n";
	print();
}
void RR() {
	process cur;
	exec a;
	int complete = 0, turnaround = 0, wait = 0, time = 0;
	seq.clear();

	for (int i = 0; i < s; i++)
		result[i].clear();
	fill(startTime.begin(), startTime.end(), -1);

	queue<process> ready;
	sort(list.begin(), list.end(), cmp_arrive);

	queue<process> q;
	for (int i = 0; i < s; i++)
		q.push(list[i]);

	while (time < total) {
		while (1) {
			if (!q.empty() && q.front().arrive == time) {
				ready.push(q.front());
				q.pop();
			}
			else break;
		}

		if (time != total && ready.empty()) {
			cout << "RR알고리즘 중간에 공백이 생겼습니다. - 잘못된 입력입니다.";
			system("pause");
			exit(1);
		}

		cur = ready.front();
		ready.pop();
		if (startTime[cur.id - 1] == -1) startTime[cur.id - 1] = time;
		int id = cur.id;
		int exe = cur.exe;
		int arrive = cur.arrive;
		a.start = time;

		if (exe <= timeSlice) {
			while (1) {
				if (!q.empty() && q.front().arrive < time + exe) {
					ready.push(q.front());
					q.pop();
				}
				else break;
			}

			a.end = a.start + exe;
			a.exe = exe;
			if (a.exe != 0) {
				result[id - 1].push_back(a);
				string s = "P" + to_string(cur.id);
				seq.push_back({ s,a });
			}
			a.start = a.end; 

			complete = time + exe;
			turnaround = complete - arrive;
			wait = complete - arrive - exeTime[id - 1];
			endTime[id - 1] = complete;
			turnaroundTime[id - 1] = turnaround;
			waitTime[id - 1] = wait;
			responseTime[id - 1] = exeTime[id - 1] + wait;
			time +=exe;
		}

		else {
			while (true) {
				if (!q.empty() && q.front().arrive < time + timeSlice) {
					ready.push(q.front());
					q.pop();
				}
				else break;
			}

			a.end = a.start + timeSlice;
			a.exe = timeSlice;
			result[id - 1].push_back(a);
			string s = "P" + to_string(cur.id);
			seq.push_back({ s,a });
			a.start = a.end; 

			cur.exe -= timeSlice;
			ready.push(cur);
			time += timeSlice;
		}
	}
	cout << "\n-------------Round-Robin algorithm--------------------------------------------------------------------\n";
	print();
}

void print() {
	cout << "\nexec time per process          \n";
	for (int i = 0; i < s; i++) {
		cout << "P" << i + 1 << " : ";
		for (int j = 0; j < result[i].size(); j++)
			cout << "(" << result[i][j].start << " ~ " <<result[i][j].end << " " << result[i][j].exe << "실행) ";
		cout << endl;
	}
	cout << "\n";

	
	cout << "\nGant Chart          \n ";
	
	for (int a = 0; a < seq.size(); a++) {
		cout << seq[a].first;
		for (int b = 0; b < seq[a].second.exe; b++)
			cout << "\t";
	}
	cout << "\n ";
	for (int a = 0; a < total; a++)
		cout << "--------";
	cout << "\n ";
	for (int a = 0; a < seq.size(); a++) {
		cout << "|";
		for (int b = 0; b < seq[a].second.exe; b++)
			cout << "\t";
	}
	cout << "|\n\n ";
	for (int a = 0; a < total; a++)
		cout << "--------";
	cout << "\n";
	for (int a = 0; a < seq.size(); a++) {
		cout << seq[a].second.start;
		for (int b = 0; b < seq[a].second.exe; b++)
			cout << "\t";
	}
	cout << seq.back().second.end<<"\n";


	cout << "\ntotal execution time:     " << total;
	double sum = 0.0;
	cout << "\nTurnaround Time:          ";
	for (int i = 0; i < s; i++) {
		cout << "P" << i + 1 << ": " << turnaroundTime[i] << "  ";
		sum += turnaroundTime[i];
	}
	cout << "\nAverage Turnaournd Time:  " << sum / (s * 1.0);

	sum = 0.0;
	cout << "\nWait Time:                ";
	for (int i = 0; i < s; i++) {
		cout << "P" << i + 1 << ": " << waitTime[i] << "  ";
		sum += waitTime[i];
	}
	cout << "\nAverage Wait Time:        " << sum / (s * 1.0) ;

	sum = 0.0;
	cout << "\nresponse Time:            ";
	for (int i = 0; i < s; i++) {
		cout << "P" << i + 1 << ": " << responseTime[i] << "  ";
		sum += responseTime[i];
	}
	cout << "\nAverage Response Time:    " << sum / (s * 1.0) << "\n\n";
}