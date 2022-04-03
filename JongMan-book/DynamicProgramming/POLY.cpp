#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 10000000;
int cache[101][101];

// n개의 정사각형으로 이루어졌고, 맨 위 가로줄에 first개의
// 정사각형을 포함하는 폴리오미노의 수를 반환함.
int Poly(int n, int first) {
	// 기저 사례: n == first
	if(n == first) return 1;
	// 메모이제이션
	int& ret = cache[n][first];
	if(ret != -1) return ret;
	ret = 0;
	for(int second = 1; second <= n-first; ++second) {
		int add = second+first-1;
		add *= Poly(n-first, second); add %= MOD;
		ret += add; ret %= MOD;
	}
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		int n; cin >> n;
		memset(cache, -1, sizeof(cache));
		int ans = 0;
		for (int i = 1; i <= n; ++i) { // ���簢�� 1������ N������
			ans += Poly(n, i);
			ans %= MOD;
		}
		cout << ans << endl;
	}
	return 0;
}