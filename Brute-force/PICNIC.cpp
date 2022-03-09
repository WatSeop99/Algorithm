#include <iostream>
using namespace std;

// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false.
int CountPairings(bool areFriends[10][10], bool taken[10], int n) {
	// 남은 학생들 중 가장 번호가 빠른 학생을 찾음.
	int firstFree = -1;
	for(int i = 0; i < n; ++i) {
		if(!taken[i]) {
			firstFree = i;
			break;
		}
	}
	// 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료함.
	if(firstFree == -1) return 1;
	int ret = 0;
	// 이 학생과 짝지을 학생을 결정함.
	for(int pairWith = firstFree+1; pairWith < n; ++pairWith) {
		if(!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += CountPairings(areFriends, taken, n);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}

int main() {
	int c, n, m;
	cin >> c;
	for(int i = 0; i < c; ++i) {
		cin >> n;
		cin >> m;
		int result = 0;
		bool areFriends[10][10] = {false}, taken[10] = {false};
		for(int j = 0; j < m; ++j) {
			int friend_1, friend_2;
			cin >> friend_1 >> friend_2;
			areFriends[friend_1][friend_2] = true;
		}
		result = CountPairings(areFriends, taken, n);
		cout << result << endl;
	}
	return 0;
}