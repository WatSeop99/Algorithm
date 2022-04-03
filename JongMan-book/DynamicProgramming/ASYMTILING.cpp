#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
int cache[101];

int Tiling(int width) {
	if(width <= 1) return 1;
	
	int& ret = cache[width];
	if(ret != -1) return ret;
	return ret = (Tiling(width-2)+Tiling(width-1))%MOD;
}

// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환함.
int Asymmetric(int width) {
	if(width%2 == 1)
		return (Tiling(width)-Tiling(width/2)+MOD)%MOD;
	int ret = Tiling(width);
	ret = (ret-Tiling(width/2)+MOD)%MOD; // (b)
	ret = (ret-Tiling(width/2-1)+MOD)%MOD; // (c)
	return ret;
}

/*int Asymmetric2(int width) {
	if(width <= 2) return 0;
	
	int& ret = cache[width];
	if(ret != -1) return ret;
	
	ret = Asymmetric2(width-2)%MOD; // (a)
	ret = (ret+Asymmetric2(width-4))%MOD; // (b)
	ret = (ret+Tiling(width-3))%MOD; // (c)
	ret = (ret+Tiling(width-3))%MOD; // (d)
	return ret;
}*/

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		int n; cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << Asymmetric(n) << endl;
	}
	return 0;
}