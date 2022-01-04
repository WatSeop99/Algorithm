#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct BipartiteUnionFind {
	// parent[i] = i의 부모노드. 루트라면 i.
	// rank[i] = i가 루트인 경우, i를 루트로 하는 트리의 랭크.
	// enemy[i] = i가 루트인 경우, 해당 집합과 적대관계인 집합의 루트번호.
	// size[i] = i가 루트인 경우, 해당 집합의 크기.
	vector<int> parent, rank, enemy, size;

	BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	// u가 속한 트리의 루트 번호를 반환.
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	// u가 속한 트리와 v가 속한 트리를 합침.
	int merge(int u, int v) {
		// u와 v가 공집합인 경우 나머지 하나를 반환.
		if (u == -1 || v == -1) return max(u, v);
		u = find(u); v = find(v);

		// 이미 둘이 같은 트리에 속한 경우.
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);

		// 이제 항상 rank[v]가 더 크므로 u를 v의 자식으로 넣음.
		if (rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
		size[v] += size[u];
		return v;
	}

	// u와 v가 서로 적대하는 집합에 속함.
	bool dis(int u, int v) {
		// 우선 루트를 찾음.
		u = find(u); v = find(v);

		// 같은 집단에 속해 있으면 모순.
		if (u == v) return false;

		// 적의 적은 나의 동지.
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}

	// u와 v가 같은 집합에 속함.
	bool ack(int u, int v) {
		// 우선 루트를 찾음.
		u = find(u); v = find(v);

		// 두 집합이 서로 적대관계면 모순.
		if (enemy[u] == v) return false;

		// 동지의 적은 나의 적
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;

		// 두 집합 다 적대하는 집합이 없으면 b는 -1일 수도 있음.
		if (b != -1) enemy[b] = a;
		return true;
	}
};

// BipartiteUnionFind 인스턴스가 주어질 때, 한 파티에 올 가능성이 있는 최대 인원을 구함.
int maxPart(const BipartiteUnionFind& buf, int n) {
	int ret = 0;
	for (int node = 0; node < n; ++node)
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];

			// 같은 모임 쌍을 두번 세지 않기 위해, enemy < node인 경우만 셈.
			// enemy == -1 인 경우도 정확히 한번 세게됨.
			if (enemy > node) continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);

			// 두 집합 중 더 큰 집합을 더함.
			ret += max(mySize, enemySize);
		}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);

	int c;
	cin >> c;
	while (c--) {
		int n, m;
		cin >> n >> m;
		BipartiteUnionFind buf(n);
		bool contradiction = false;
		int cont_idx = -1;
		for (int i = 0; i < m; ++i) {
			string str = "";
			int a, b;
			cin >> str >> a >> b;
			if (contradiction) continue;
			if (str == "ACK") {
				if (buf.ack(a, b) == false) {
					contradiction = true;
					cont_idx = i + 1;
				}
			}
			else {
				if (buf.dis(a, b) == false) {
					contradiction = true;
					cont_idx = i + 1;
				}
			}
		}
		if (contradiction)
			cout << "CONTRADICTION AT " << cont_idx << "\n";
		else {
			int result = maxPart(buf, n);
			cout << "MAX PARTY SIZE IS " << result << "\n";
		}
	}
	return 0;
}