#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

const int MAX_V = 10000;

// 정점과 간선의 개수.
int V, E;

// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담음.
vector<pair<int, double>> adj[MAX_V];

vector<double> dijkstra(int src) {
	vector<double> dist(V, numeric_limits<double>::max());
	dist[src] = 1.0;
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1.0, src));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 거낸 것보다 더 짧은 경로를 알고 있다면 꺼낸 것을 무시함.
		if (dist[here] < cost) continue;
		// 인접한 정점들을 모두 검사함.
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			double nextDist = cost * adj[here][i].second;
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
		cin >> V >> E;
		for (int i = 0; i < V; ++i)
			adj[i].clear();
		for (int i = 0; i < E; ++i) {
			int a, b;
			double c;
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}
		vector<double> result = dijkstra(0);
		printf("%.10f\n", result[V - 1]);
	}
	return 0;
}