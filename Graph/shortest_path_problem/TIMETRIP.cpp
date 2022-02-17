#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_V = 100, INF = 987654321;

// 정점의 개수.
int V;
// 그래프의 인접리스트. (연결된 번호, 간선가중치) 쌍을 담음.
vector<pair<int, int>> adj[MAX_V];
// reachable[u][v] = u에서 v로 가는 경로가 있을까?
bool reachable[MAX_V][MAX_V];

// src에서 target으로 가는 최단거리를 계산함.
// 가중치가 음의 무한대인 경로가 있으면 -INF를 반환함.
int bellman2(int src, int target) {
	// 시작점을 제외한 모든 정점까지의 최단거리 상한을 INF로 둠.
	vector<int> upper(V, INF);
	upper[src] = 0;
	// V-1번 순환함.
	for (int iter = 0; iter < V - 1; ++iter)
		for (int here = 0; here < V; ++here)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// (here, there) 간선을 따라 완화를 시도.
				upper[there] = min(upper[there], upper[here] + cost);
			}
	// 음수 사이클의 존재여부를 확인함.
	for (int here = 0; here < V; ++here)
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			// 완화가 성공한다면 here에는 음수사이클이 있음.
			if (upper[here] + cost < upper[there])
				// 이 음수 사이클을 포함하는 경로가 있는가?
				if (reachable[src][here] && reachable[here][target])
					return -INF;
		}
	return upper[target];
}


int main() {
	int c;
	cin >> c;
	while (c--) {
		int W;
		cin >> V >> W;
		for (int i = 0; i < V; ++i)
			adj[i].clear();
		memset(reachable, false, sizeof(reachable));
		for (int i = 0; i < V; ++i)
			reachable[i][i] = true;
		int a, b, d;
		for (int i = 0; i < W; ++i) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(b, d));
			reachable[a][b] = true;
		}
		int shortest = bellman2(0, 1);
		if (shortest == INF) {
			cout << "UNREACHABLE\n";
			continue;
		}
		if (shortest == -INF)
			cout << "INFINITY ";
		else
			cout << shortest << ' ';
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < adj[i].size(); ++j)
				adj[i][j].second = -adj[i][j].second;
		int longest = bellman2(0, 1);
		if (longest == -INF)
			cout << "INFINITY\n";
		else
			cout << -longest << '\n';
	}
	return 0;
}