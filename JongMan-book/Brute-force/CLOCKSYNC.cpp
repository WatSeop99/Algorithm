#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

// linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있음.
// linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않음.
const char linked[SWITCHES][CLOCKS+1] = {
	// 0123456789012345
	"xxx.............", "...x...x.x.x....",
	"....x.....x...xx", "x...xxxx........",
	"......xxx.x.x...", "x.x...........xx",
	"...x..........xx", "....xx.x......xx",
	".xxxxx..........", "...xxx...x...x.."
};

// 모든 시계가 12시를 가리키고 있는지를 확인함.
bool AreAligned(const vector<int>& clocks) {
	for(int i = 0; i < clocks.size(); ++i) {
		if(clocks[i] != 12) return false;
	}
	return true;
}

// swtch번 스위치를 누름.
void Push(vector<int>& clocks, int swtch) {
	for(int clock = 0; clock < CLOCKS; ++clock) {
		if(linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if(clocks[clock] == 15) clocks[clock] = 3;
		}
	}
}

// clocks: 현재 시계들의 상태.
// swtch: 이번에 누를 스위치의 번호.
// clocks과 swtch가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환함.
// 만약 불가능하다면 INF 이상의 큰 수를 반환함.
int Solve(vector<int>& clocks, int swtch) {
	if(swtch == SWITCHES) return AreAligned(clocks) ? 0 : INF;
	// 이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도함.
	int ret = INF;
	for(int cnt = 0; cnt < 4; ++cnt) {
		ret = min(ret, cnt+Solve(clocks, swtch+1));
		Push(clocks, swtch);
	}
	// push(clocks, swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 됨.
	return ret;
}

int main(void) {
	int c;
	cin >> c;
	for(int tc = 0; tc < c; ++tc) {
		vector<int> clocks(16, 0);
		int result;
		for(int i = 0; i < clocks.size(); ++i)
			cin >> clocks[i];
		result = Solve(clocks, 0);
		if(result >= INF) cout << -1 << endl;
		else cout << result << endl;
	}
	return 0;
}