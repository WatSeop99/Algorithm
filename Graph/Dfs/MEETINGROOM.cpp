#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

// 그래프의 인접리스트 표현.
vector<vector<int>> adj;
// 두 구간 a와 b가 서로 겹치지 않는지 확인함.
bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second <= b.first || b.second <= a.first;
}

// metting[]가 각 팀이 하고 싶어하는 회의 시간의 목록일 때,
// 이를 2SAT 문제로 변환한 뒤 함의 그래프를 생성함.
// i번팀은 meetings[2*i] 혹은 mettings[2*i+1]중 하나 시간에 회의실을 써야함.
void makeGraph(const vector<pair<int, int>>& meetings) {
	int vars = meetings.size();
	// 그래프는 각 변수마다 두 개의 정점을 가짐.
	adj.clear(); adj.resize(vars * 2);
	for (int i = 0; i < vars; i += 2) {
		// 각 팀은 i번 회의나 j번 회의 둘 중 하나는 해야함.
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2); // ~i => j
		adj[j * 2 + 1].push_back(i * 2); // ~j => i
	}
	for (int i = 0; i < vars; ++i)
		for (int j = 0; j < i; ++j) {
			// i번 회의와 j번 회의가 겹칠 경우
			if (!disjoint(meetings[i], meetings[j])) {
				// i번 회의가 열리지 않거나, j번 회의가 열리지 않아야 함.
				// (~i or ~j)절을 추가함.
				adj[i * 2].push_back(j * 2 + 1);
				adj[j * 2].push_back(i * 2 + 1);
			}
		}
}

// 각 정점의 컴포넌트 번호.
// 컴포넌트 번호는 0부터 시작하여 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같음.
vector<int> sccId;
// 각 정점의 발견 순서.
vector<int> discovered;
// 정점의 번호를 담는 스택.
stack<int> st;
int sccCounter, vertexCounter;

// here을 루트로 하는 서브트리에서 역방향 간선이나 교차간선을 통해 갈 수 있는
// 정점 중 최소 발견 순서를 반환함.
// (이외 SCC로 묶인 정점으로 연결된 교차간선은 무시함.)
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// 스택에 here를 넣음. here의 후손들은 모두 스택에서 here 후 들어감.
	st.push(here);
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		// (here, there)가 트리 간선.
		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// there가 무시해야 하는 교차간선이 아니라면.
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	// here에서 부모로 올라가는 간선을 끊어야 할지 확인함.
	if (ret == discovered[here]) {
		// here을 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶음.
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here) break;
		}
		++sccCounter;
	}
	return ret;
}

// tarjan의 SCC알고리즘.
vector<int> tarjanSCC() {
	// 배열들을 전부 초기화.
	sccId = discovered = vector<int>(adj.size(), -1);
	// 카운터 초기화.
	sccCounter = vertexCounter = 0;
	// 모든 정점에 대해 SCC호출.
	for (int i = 0; i < adj.size(); ++i)
		if (discovered[i] == -1) scc(i);
	return sccId;
}

// adj에 함의 그래프의 인접 리스트 표현이 주어질 때, 2-SAT의 답을 반환함.
vector<int> solve2SAT() {
	// 변수의 수.
	int n = adj.size() / 2;
	// 함의 그래프의 정점들을 강결합 요소별로 묶음.
	vector<int> label = tarjanSCC();
	// 이 SAT문제를 푸는 것이 불가능한지 확인함.
	// 한 변수를 나타내는 두 정점이 같은 강결합 요소에 속해있을 경우 답은 없음.
	for (int i = 0; i < 2 * n; i += 2)
		if (label[i] == label[i + 1])
			return vector<int>();
	// SAT 문제를 푸는 것이 가능함.
	vector<int> value(2 * n, -1);
	// Tarjan 알고리즘에서 SCC번호는 위상정렬의 역순으로 배정됨.
	// SCC의 번호를 역순으로 각 정점을 정렬하면 위상정렬 순서가 됨.
	vector<pair<int, int>> order;
	for (int i = 0; i <2 * n; ++i)
		order.push_back(make_pair(-label[i], i));
	sort(order.begin(), order.end());
	// 각 정점에 값을 배정함.
	for (int i = 0; i < 2 * n; ++i) {
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex % 2 == 0;
		if (value[variable] != -1) continue;
		// notA가 A보다 먼저 나왔으면 A는 참.
		// A가 notA보다 먼저 나왔으면 A는 거짓.
		value[variable] = !isTrue;
	}
	return value;
}

int main() {
	int c; 
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		vector<pair<int, int>> arr;
		for (int i = 0; i < n; ++i) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			arr.push_back(make_pair(a, b));
			arr.push_back(make_pair(c, d));
		}
		makeGraph(arr);
		vector<int> result = solve2SAT();
		if (result.empty())
			cout << "IMPOSSIBLE\n";
		else {
			cout << "POSSIBLE\n";
			for (int i = 0; i < 2 * n; i += 2) {
				if (result[i] == 1)
					cout << arr[i].first << ' ' << arr[i].second << '\n';
				else
					cout << arr[i + 1].first << ' ' << arr[i + 1].second << '\n';
			}
		}
	}
	return 0;
}