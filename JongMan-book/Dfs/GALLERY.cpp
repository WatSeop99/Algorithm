#include <iostream>
#include <vector>
using namespace std;

const int MAX_V = 1000;

int V;
vector<int> adj[MAX_V];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
// 지금까지 설치한 카메라 총 수.
int installed;

// here부터 깊이 우선 탐색을 하고, here의 정보를 반환함.
int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0, 0, 0 };
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (!visited[there])
			++children[dfs(there)];
	}
	// 자손 노드 중 감시되지 않은 노드가 있을 경우 카메라를 설치함.
	if (children[UNWATCHED]) {
		++installed;
		return INSTALLED;
	}
	// 자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없음.
	if (children[INSTALLED])
		return WATCHED;
	return UNWATCHED;
}

// 그래프를 감시하는데 필요한 카메라의 최소 수를 반환함.
int installCamera() {
	installed = 0;
	visited = vector<bool>(V, false);
	for (int u = 0; u < V; ++u) {
		if (!visited[u] && dfs(u) == UNWATCHED)
			++installed;
	}
	return installed;
}

int main() {
	int c;
	cin >> c;
	while (c--) {
		int E;
		cin >> V >> E;
		for (int i = 0; i < V; ++i) adj[i].clear();
		for (int i = 0; i < E; ++i) {
			int v1, v2;
			cin >> v1 >> v2;
			adj[v1].push_back(v2);
			adj[v2].push_back(v1);
		}
		cout << installCamera() << '\n';
	}
	return 0;
}