#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <utility>
using namespace std;

const int ALPHABETS = 26;
const int MOD = 10007;
int cache[101][1001];

int toNumber(char ch) { return ch-'a'; }

struct TrieNode {
	TrieNode* children[ALPHABETS];
	TrieNode* next[ALPHABETS]; // 해당 노드가 표현하는 문자열 뒤에 어떤 문자를 붙였을 때, 어떤 노드로 가는지 나타냄.
	TrieNode* fail; // 실패 연결.
	vector<int> output; // 출력 문자열 목록.
	int terminal; // 현 위치에서 끝나는 문자열 번호.
	int no; // 해당 노드의 번호.

	TrieNode() : terminal(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i)
			if (children[i]) delete children[i];
	}

	void insert(const char* key, int id) {
		if (*key == 0) terminal = id;
		else {
			int next = toNumber(*key);
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			children[next]->insert(key+1, id);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == nullptr) return nullptr;
		return children[next]->find(key+1);
	}
};

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열을 계산함.
void computeFailFunc(TrieNode* root) {
	// 루트에서부터 시작해 한 단계씩 아래로 내려가면서 각 노드의 실패 연결을 계산함.
	queue<TrieNode*> q;
	// 루트의 실패 연결은 자기자신.
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// here의 모든 자손에 대해 실패 연결을 계산하고 이들을 큐에 넣음.
		for (int edge = 0; edge < ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			// 1레벨 노드의 실패 연결은 항상 루트.
			if (here == root) child->fail = root;
			else {
				// 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾음.
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == nullptr)
					t = t->fail;
				if (t->children[edge])
					t = t->children[edge];
				child->fail = t;
			}
			// 출력 문자열 실패 목록
			// 실패 연결을 따라간 노드에서 복사해온 뒤, 이 위치에서 끝나는 바늘 문자열이 있으면 추가함.
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

// 앞으로 length 글자를 더 만들어야 하는데, 
// 아호-코라식 알고리즘의 현재 상태가 state에 주어질 때 IDS에 걸리지 않는 문자열의 수는?
int count(int length, TrieNode* state) {
	// 기저사례 : 이 상태에 문자열이 충돌하면 곧장 종료.
	if (state->output.size()) return 0;
	// 기저사례 : 문자열을 전부 만든 경우.
	if (length == 0) return 1;
	int& ret = cache[length][state->no];
	if (ret != -1) return ret;
	ret = 0;
	// 다음으로 letter의 글자를 넣을 경우.
	for (int letter = 0; letter < ALPHABETS; ++letter) {
		ret += count(length-1, state->next[letter]);
		ret %= MOD;
	}
	return ret;
}

// 상태 간의 전이 테이블을 next[]에 채움. coumputeFailFunc()를 통해 이미 실패 함수가 계산되어 있다고 가정함.
void computeTransition(TrieNode* here, int& nodeCounter) {
	// 0에서 시작하는 번호를 매김 : cache[]의 인덱스.
	here->no = nodeCounter++;
	// here 뒤에 글자 chr를 붙였을 때 어디로 가는가?
	for (int chr = 0; chr < ALPHABETS; ++chr) {
		// next[]값을 계산해 저장.
		TrieNode* next = here;
		while (next != next->fail && next->children[chr] == nullptr)
			next = next->fail;
		if (next->children[chr]) next = next->children[chr];
		here->next[chr] = next;
		// 재귀적으로 모든 노드에 대해 전이 테이블을 계산함.
		if (here->children[chr])
			computeTransition(here->children[chr], nodeCounter);
	}
}

int solve(int length, const vector<string>& patterns) {
	TrieNode trie;
	for (int i = 0; i < patterns.size(); ++i)
		trie.insert(patterns[i].c_str(), i);
	computeFailFunc(&trie);
	int countNode = 0;
	computeTransition(&trie, countNode);
	return count(length, &trie);
}

int main(void) {
	int c;
	cin >> c;
	while (c--) {
		for (int i = 0; i < 101; ++i)
			memset(cache[i], -1, sizeof(int) * 1001);
		int n, m;
		cin >> n >> m;
		vector<string> patterns(m);
		for (int i = 0; i < m; ++i)
			cin >> patterns[i];
		cout << solve(n, patterns) << '\n';
	}
	return 0;
}