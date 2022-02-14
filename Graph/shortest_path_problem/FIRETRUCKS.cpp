#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>
#include <limits>
using namespace std;

const int MAX_V = 1001;

// 정점과 간선의 개수.
int V, E;

// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담음.
vector<pair<int, int>> adj[MAX_V];

vector<int> dijkstra(int src) {
	vector<int> dist(V + 1, numeric_limits<int>::max());
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시함.
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣음.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int main() {
	int c;
	cin >> c;
	while (c--) {
		int n, m;
		cin >> V >> E >> n >> m;
		for (int i = 0; i < V + 1; ++i)
			adj[i].clear();
		for (int i = 0; i < E; ++i) {
			int a, b, t;
			cin >> a >> b >> t;
			adj[a].push_back(make_pair(b, t));
			adj[b].push_back(make_pair(a, t));
		}
		vector<int> firePlace(n);
		for (int i = 0; i < n; ++i)
			cin >> firePlace[i];
		for (int i = 0; i < m; ++i) {
			int fireStation;
			cin >> fireStation;
			adj[0].push_back(make_pair(fireStation, 0));
			adj[fireStation].push_back(make_pair(0, 0));
		}
		vector<int> result = dijkstra(0);
		int sum = 0;
		for (int i = 0; i < firePlace.size(); ++i)
			sum += result[firePlace[i]];
		cout << sum << '\n';
	}
	return 0;
}