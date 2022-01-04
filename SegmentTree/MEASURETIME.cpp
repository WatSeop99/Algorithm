#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n+1) {}
	
	// A[0...pos]의 부분합을 구함.
	int Sum(int pos) {
		// index는 1부터 시작
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// 다음 구간을 찾기 위해 최종비트 지움.
			pos &= (pos-1);
		}
		return ret;
	}

	// A[pos]에 val을 더함.
	void Add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

long long CountMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.Sum(999999)-tree.Sum(A[i]);
		tree.Add(A[i], 1);
	}
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		vector<int> arr;
		for (int i = 0; i < n; ++i) {
			int num;
			cin >> num;
			arr.push_back(num);
		}
		int ret = CountMoves(arr);
		cout << ret << '\n';
	}
	return 0;
}