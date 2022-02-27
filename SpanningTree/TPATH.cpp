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

const int MAX_V = 500, INF = 987654321;
int V, E;
// 모든 간선의 가중치 목록. 정렬해 둠.
vector<int> weights;
// (가중치, (정점1, 정점2))의 목록. 미리 정렬해 둠.
vector<pair<int, pair<int, int>>> edges;

// 가중치가 weights[low] 이상인 간선으로 시작점과 도착점을 연결하는
// 경로를 만들기 위해 필요한 경로의 최소 상한을 계산함.
// 두 정점을 연결 할 수 없을 경우 큰 값을 반환함.
int kruskalMinUpperBound(int low) {
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); ++i) {
		if (edges[i].first < weights[low]) continue;
		// edges[i]를 그래프에 추가함.
		sets.merge(edges[i].second.first, edges[i].second.second);
		// 0과 V-1이 연결되었다면 마지막 추가한 간선의 가중치를 반환.
		if (sets.find(0) == sets.find(V - 1))
			return edges[i].first;
	}
	return INF;
}

// 0과 V-1을 연결하는 경로 중 가중치의 상한과 하한 차이의 최소값을 계산.
int minWeightDifference() {
	int ret = INF;
	for (int i = 0; i < weights.size(); ++i)
		ret = min(ret, kruskalMinUpperBound(i) - weights[i]);
	return ret;
}


int main() {
	int c;
	cin >> c;
	while (c--) {
		cin >> V >> E;
		weights.resize(E);
		edges.resize(E);
		for (int i = 0; i < E; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			edges[i] = make_pair(c, make_pair(a, b));
			weights[i] = c;
		}
		sort(weights.begin(), weights.end());
		sort(edges.begin(), edges.end());
		cout << minWeightDifference() << '\n';
	}
	return 0;
}