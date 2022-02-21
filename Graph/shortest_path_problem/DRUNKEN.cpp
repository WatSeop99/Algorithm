#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 987654321;

// 그래프의 인접 행렬 표현.
int V, adj[500][500];
// 각 정점에서 음주 운전 단속을 할 때 걸리는 시간.
int delay[500];
int W[500][500];

// 입력을 받을 때 1부터 시작하는 정점 번호를 0부터 시작하도록 변경했다고 가정함.
void solve() {
	// 모든 정점들을 예상 시간 별로 정렬함.
	vector<pair<int, int>> order;
	for (int i = 0; i < V; ++i)
		order.push_back(make_pair(delay[i], i));
	sort(order.begin(), order.end());
	// 정점을 하나도 거치지 않고 얻을 수 있는 최단 경로.
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j) {
			if (i == j) W[i][j] = 0;
			else W[i][j] = adj[i][j];
		}
	int ret = INF;
	for (int k = 0; k < V; ++k) {
		// k번째로 예상 시간이 적게 걸리는 정점W까지를 지나서 얻을 수 있는 최단 거리.
		int w = order[k].second;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(adj[i][w] + delay[w] + adj[w][j], W[i][j]);
			}
	}
}


int main() {
	int E;
	cin >> V >> E;
	memset(delay, 0x3f, sizeof(delay));
	memset(adj, 0x3f, sizeof(adj));
	for (int i = 0; i < V; ++i)
		cin >> delay[i];
	for (int i = 0; i < E; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		a -= 1; b -= 1;
		adj[a][b] = adj[b][a] = c;
	}
	solve();
	int t;
	cin >> t;
	while (t--) {
		int s, t;
		cin >> s >> t;
		cout << W[s - 1][t - 1] << '\n';
	}
	return 0;
}