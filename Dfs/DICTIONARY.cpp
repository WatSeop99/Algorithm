#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 알파벳의 각 글자에 대한 인접 행렬 표현.
// 간선 (i, j)는 알파벳 i가 j보다 앞에 와야 함을 나타냄.
vector<vector<int>> adj;

// 주어진 단어들로부터 알파벳 선후관계를 그래프로 생성함.
void makeGraph(const vector<string>& words) {
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int j = 1; j < words.size(); ++j) {
		int i = j-1, len = min(words[i].size(), words[j].size());
		// word[i]가 word[j] 앞에 오는 이유를 찾음.
		for (int k = 0; k < len; ++k) {
			if (words[i][k] != words[j][k]) {
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}
		}
	}
}

vector<int> seen, order;

void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < adj.size(); ++there)
		if (adj[here][there] && !seen[there]) dfs(there);
	order.push_back(here);
}

// adj에 주어진 그래프를 위상정렬한 결과를 반환함.
// 그래프가 DAG가 아니라면 빈 벡트를 반환.
vector<int> topologicalSort(void) {
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();
	for (int i = 0; i < m; ++i)
		if (!seen[i]) dfs(i);
	reverse(order.begin(), order.end());
	// 만약 그래프가 DAG가 아니라면 정렬 결과에 역방향 간선이 존재함.
	for (int i = 0; i < m; ++i)
		for (int j = i+1; j < m; ++j)
			if (adj[order[j]][order[i]])
				return vector<int>();
	// 없는 경우라면 깊이 우선 탐색에서 얻은 순서를 반환함.
	return order;
}

int main(void) {
	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		vector<string> arr(n);
		for (int i = 0; i < n; ++i)
			cin >> arr[i];
		makeGraph(arr);
		vector<int> result = topologicalSort();
		if (!result.empty()) {
			for (int i = 0; i < result.size(); ++i)
				cout << char(result[i]+'a');
			cout << '\n';
		}
		else cout << "INVALID HYPOTHESIS" << '\n';
	}
	return 0;
}