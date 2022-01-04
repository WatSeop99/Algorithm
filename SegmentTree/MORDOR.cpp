#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = numeric_limits<int>::max();

void getMinus(int& num) {
	num *= -1;
}

struct RMQ {
	int n; // 배열의 길이.
	vector<int> rangeMin; // 각 구간의 최소치.
	
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n*4);
		init(array, 0, n-1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left+right)/2;
		int leftMin = init(array, left, mid, node*2);
		int rightMin = init(array, mid+1, right, node*2+1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 두 구간이 겹치지 않으면 아주 큰 값을 반환 : 무시됨.
		if (right < nodeLeft || nodeRight < left) return MAX;

		// node가 표현하는 범위가 array[left ... right]에 완전히 포함되는 경우.
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];

		// 양쪽 구간을 나눠서 푼 뒤 합침.
		int mid = (nodeLeft+nodeRight)/2;
		return min(query(left, right, node*2, nodeLeft, mid), query(left, right, node*2+1, mid+1, nodeRight));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// index가 노드가 표현하는 구간과 상관없는 경우 무시함.
		if (index < nodeLeft || nodeRight < index) return rangeMin[node];

		// 트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;

		int mid = (nodeLeft+nodeRight)/2;
		return rangeMin[node] = min(update(index, newValue, node*2, nodeLeft, mid), update(index, newValue, node*2+1, mid+1, nodeRight));
	}

	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n-1);
	}
};

int main(void) {
	int c;
	cin >> c;
	while (c--) {
		int n, q;
		cin >> n >> q;
		vector<int> high(n);
		for (int i = 0; i < n; ++i)
			cin >> high[i];
		RMQ minTree(high);
		for_each(high.begin(), high.end(), getMinus);
		RMQ maxTree(high);
		for (int i = 0; i < q; ++i) {
			int first, last;
			cin >> first >> last;
			cout << -maxTree.query(first, last)-minTree.query(first, last) << '\n';
		}
	}
	return 0;
}