#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 987654321;

// 정점의 개수.
int V;
// 그래프의 인접 행렬 표현.
int adj[200][200];

// 플로이드의 모든 쌍 최단 거리 알고리즘.
void floyd() {
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

// 간선 (a, b)를 추가했을 때 그래프의 최단 거리 배열 adj를 적절히 갱신함.
// 간선이 아무런 의미가 없을 경우 false를 반환함.
bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; ++x)
		for (int y = 0; y < V; ++y)
			// x~y 최단경로가 (a, b)를 이용하려면
			// x~a-b~y 혹은 x~b-a~y의 형태를 가져야 함.
			adj[x][y] = min(adj[x][y], min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[a][y]));
	return true;
}


int main() {
	int c;
	cin >> c;
	while (c--) {
		int M, N;
		cin >> V >> M >> N;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j) {
				if (i == j) adj[i][j] = 0;
				else adj[i][j] = INF;
			}
		for (int i = 0; i < M; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a][b] = adj[b][a] = min(adj[b][a], c);
		}
		floyd();
		int count = 0;
		for (int i = 0; i < N; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			if (!update(a, b, c)) count++;
		}
		cout << count << '\n';
	}
	return 0;
}