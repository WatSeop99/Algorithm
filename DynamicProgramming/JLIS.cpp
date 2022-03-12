#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// 입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
// 인위적인 최소치는 64비트여야 함.
const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache [101][101];

// min(A[indexA], B[indexB]), max(A[indexA], B[indexB])로 시작하는
// 합친 증가 부분 수열의 최대 길이를 반환함.
// 단, indexA == indexB == -1 혹은 A[indexA] != B[indexB]라고 가정함.
int Jlis(int indexA, int indexB) {
	// 메모이제이션
	int& ret = cache[indexA+1][indexB+1];
	if(ret != -1) return ret;
	// A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있음.
	ret = 2;
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);
	// 다음 원소를 찾음.
	for(int nextA = indexA+1; nextA < n; ++nextA)
		if(maxElement < A[nextA])
			ret = max(ret, Jlis(nextA, indexB)+1);
	for(int nextB = indexB+1; nextB < m; ++nextB)
		if(maxElement < B[nextB])
			ret = max(ret, Jlis(indexA, nextB)+1);
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		cin >> n; cin >> m;
		memset(cache, -1, sizeof(cache));
		for(int i = 0; i < n; ++i)
			cin >> A[i];
		for(int i = 0; i < m; ++i)
			cin >> B[i];
		cout << Jlis(-1, -1)-2 << endl;
	}
	return 0;
}