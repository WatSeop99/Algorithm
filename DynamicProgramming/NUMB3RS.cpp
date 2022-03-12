#include <iostream>
#include <cstring>
using namespace std;

int n, d, p, q;
double cache[51][101];
// connected[i][j] = 마을 i, j가 연결되어 있나 여부.
// deg[i] = 마을 i와 연결된 마을의 개수.
int connected[51][51], deg[51];

double Search3(int here, int days) {
	// 기저 사례: 0일째
	if(days == 0) return (here == p ? 1.0 : 0.0);
	// 메모이제이션
	double& ret = cache[here][days];
	if(ret > -0.5) return ret;
	ret = 0.0;
	for(int there = 0; there < n; ++there)
		if(connected[here][there])
			ret += Search3(there, days-1)/deg[there];
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		cin >> n; cin >> d; cin >> p;
		for(int i = 0; i < 51; ++i)
			memset(cache[i], -1.0, sizeof(double)*101);
		for(int i = 0; i < n; ++i) {
			int count = 0;
			for(int j = 0; j < n; ++j) {
				cin >> connected[i][j];
				if(connected[i][j]) count++;
			}
			deg[i] = count;
		}
		int t; cin >> t;
		while(t--) {
			cin >> q;
			cout << fixed;
    		cout.precision(8);
			cout << Search3(q, d) << " ";
		}
		cout << endl;
	}
	return 0;
}