#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

// -1은 아직 답이 계산되지 않았음을 의미.
// 1은 해당 입력들이 서로 대응됨을 의미.
// 0은 해당 입력들이 서로 대응되지 않음을 의미.
int cache [101][101];

// 와일드카드 패턴 W[w...]가 문자열 S[s...]에 대응되는지 여부를 반환함.
bool MatchMemoized(const string& W, const string& S, int w, int s) {
	// 메모이제이션
	int& ret = cache[w][s];
	if(ret != -1) return ret;
	// W[w]와 S[s]를 맞춰나감.
	if(w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
		return ret = MatchMemoized(W, S, w+1, s+1);
	// 더 이상 대응할 수 없으면 왜 재귀호출이 끝났는지 확인함.
	// 2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 함.
	if(w == W.size()) return ret = (s == S.size());
	// 4. *를 만나서 끝난 경우: *에 몇 글자를 대응해야 할 지 재귀 호출하면서 확인함.
	if(W[w] == '*') {
		if(MatchMemoized(W, S, w+1, s) || (s < S.size() && MatchMemoized(W, S, w, s+1)))
			return ret = 1;
	}
	// 3. 이 외의 경우에는 모두 대응되지 않음.
	return ret = 0;
}

int main(void) {
	int c;
	cin >> c;
	while(c--) {
		string W;
		vector<string> S;
		cin >> W;
		int input; cin >> input;
		for(int i = 0; i < input; ++i) {
			memset(cache, -1, sizeof(cache));
			string s; cin >> s;
			if(MatchMemoized(W, s, 0, 0))
				S.push_back(s);
		}
		sort(S.begin(), S.end());
		for(int i = 0; i < S.size(); ++i)
			cout << S[i] << endl;
	}
	return 0;
}