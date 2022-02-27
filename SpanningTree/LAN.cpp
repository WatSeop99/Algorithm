#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

struct DisjointSet {
	vector<int> parent, rank;
	
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	// u가 속한 트리의 루트의 번호를 반환함.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	// u가 속한 트리와 v가 속한 트리를 합침.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// u와 v가 이미 같은 집합에 속하는 경우를 걸러냄.
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		// 이제 rank[v]가 항상 rank[u] 이상이므로 u를 v의 자식으로 넣음.
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}
};

const int MAX_V = 500;

// 정점과 간선의 개수.
int V, E;
// (x, y) 좌표.
pair<int, int> pos[MAX_V];

// 주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선 가중치의 합을 반환.
double kruskal(DisjointSet& sets) {
	double ret = 0;
	// (가중치, (정점1, 정점2))의 목록을 얻음.
	vector<pair<double, pair<int, int>>> edges;
	for(int i = 0; i < V; ++i)
		for (int j = i + 1; j < V; ++j)
			if (sets.find(i) != sets.find(j))
				edges.push_back(make_pair(hypot(pos[i].first - pos[j].first, pos[i].second - pos[j].second), make_pair(i, j)));
	sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); ++i) {
		double weight = edges[i].first;
		int a = edges[i].second.first, b = edges[i].second.second;
		if (sets.find(a) != sets.find(b)) {
			ret += weight;
			sets.merge(a, b);
		}
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	while (c--) {
		cin >> V >> E;
		for (int i = 0; i < V; ++i) cin >> pos[i].first;
		for (int i = 0; i < V; ++i) cin >> pos[i].second;
		DisjointSet sets(V);
		for (int i = 0; i < E; ++i) {
			int a, b;
			cin >> a >> b;
			sets.merge(a, b);
		}
		double ret = kruskal(sets);
		printf("%.10lf\n", ret);
	}
	return 0;
}