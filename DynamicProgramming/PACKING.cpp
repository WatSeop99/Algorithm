#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int n, capacity;
int volume[100], need[100];
int cache[1001][100];
string name[100];

// 캐리어에 남은 용량이 capacity일 때, item이후의 물건들을
// 담아 얻을 수 잇는 최대 절박도의 합을 반환함.
int Pack(int capacity, int item) {
	// 기저 사례: 더 담을 물건이 없을 때.
	if(item == n) return 0;
	int& ret = cache[capacity][item];
	if(ret != -1) return ret;
	// 이 물건을 담지 않을 경우.
	ret = Pack(capacity, item+1);
	// 이 물건을 담을 경우.
	if(capacity >= volume[item])
		ret = max(ret, Pack(capacity-volume[item], item+1)+need[item]);
	return ret;
}

// pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장함.
void Reconstruct(int capacity, int item, vector<string>& picked) {
	// 기저 사례: 모든 물건을 다 고려했음.
	if(item == n) return;
	if(Pack(capacity, item) == Pack(capacity, item+1))
		Reconstruct(capacity, item+1, picked);
	else {
		picked.push_back(name[item]);
		Reconstruct(capacity-volume[item], item+1, picked);
	}
}

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		cin >> n; cin >> capacity;
		vector<string> picked;
		
		for(int i = 0; i < 1001; ++i)
			memset(cache[i], -1, sizeof(int)*100);
		
		for(int i = 0; i < n; ++i) {
			cin >> name[i];
			cin >> volume[i];
			cin >> need[i];
		}
		cout << Pack(capacity, 0) << " ";
		Reconstruct(capacity, 0, picked);
		cout << picked.size() << endl;
		for(int i = 0; i < picked.size(); ++i)
			cout << picked[i] << endl;
	}
	return 0;
}