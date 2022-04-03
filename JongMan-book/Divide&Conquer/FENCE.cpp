#include <iostream>
#include <algorithm>
using namespace std;

// 각 판자의 높이를 저장하는 배열.
int h[20001];

// h[left...right] 구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이를 반환함.
int Solve(int left, int right) {
	// 기저 사례: 판자가 하나밖에 없는 경우.
	if(left == right) return h[left];
	// [left, mid], [mid+1, right]의 두 구간으로 문제를 분할함.
	int mid = (left+right)/2;
	// 분할한 문제들을 각개격파.
	int ret = max(Solve(left, mid), Solve(mid+1, right));
	// 부분 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾음.
	int lo = mid, hi = mid+1;
	int height = min(h[lo], h[hi]);
	// [mid, mid+1]만 포함하는 너비 2인 사각형을 고려함.
	ret = max(ret, height*2);
	// 사각형ㅇ이 입력 전체를 덮을 때까지 확장해 나감.	
	while(left < lo || hi < right) {
		// 항상 높이가 더 높은 쪽으로 확장함.
		if(hi < right && (lo == left || h[lo-1] < h[hi+1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}
		// 확장한 후 사각형의 넓이.
		ret = max(ret, height*(hi-lo+1));
	}
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	for(int tc = 0; tc < c; ++tc) {
		int n;
		cin >> n;
		for(int i = 0; i < n; ++i)
			cin >> h[i];
		cout << Solve(0, n-1) << endl;
	}
	return 0;
}