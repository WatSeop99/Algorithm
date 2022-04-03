#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'A'; }

struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 이 노드에서 종료하는 문자열의 번호. 없으면 -1.
	int terminal;
	// 이 노드에서 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화.
	int first;
	TrieNode() : terminal(-1), first(-1) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i)
			if (children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가함.
	void insert(const char* key, int id) {
		// first를 우선 갱신
		if (first == -1) first = id;
		// 문자열이 끝났다면 terminal만 바꾸고 종료.
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식노드가 없다면 생성함.
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			// 해당 자식노드로 재귀호출.
			children[next]->insert(key+1, id);
		}
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾음. 없으면 NULL 반환.
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == nullptr) return nullptr;
		return children[next]->find(key+1);
	}

	// 이 노드까지 타이핑해 왔을 때, 번호 id인 key를 타이핑 하기 위해 최소 몇 번의 키를 눌러야 하는가?
	int type(const char* key, int id) {
		// 문자열 종료 시.
		if (*key == 0) return 0;
		// 이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료.
		if (first == id) return 1;
		// 아니면 다음 문자를 타이핑.
		int next = toNumber(*key);
		return 1+children[next]->type(key+1, id);
	}
};

// 사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는데 몇 번의 키를 눌러야 하는지 계산.
int countKeys(TrieNode* trie, const char* word) {
	// 이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구함.
	TrieNode* node = trie->find(word);
	// 사전에 없으면 직접 타이핑할 방법을 찾음.
	if (node == nullptr || node->terminal == -1)
		return strlen(word);
	// 탐색하며 타이핑할 방법을 찾음.
	return trie->type(word, node->terminal);
}

// 입력에 주어지는 단어들을 정렬하여 트라이로 변환함.
TrieNode* readInput(int words) {
	// 단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬함.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; ++i) {
		char buf[11];
		int freg;
		scanf("%s %d", buf, &freg);
		input.push_back(make_pair(-freg, buf));
	}
	sort(input.begin(), input.end());
	// 이때 앞에 있는 단어일수록 우선순위가 높음. 배열 인덱스를 각 단어의 번호로 씀.
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); ++i)
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}

int main(void) {
	int c;
	scanf("%d", &c);
	while (c--) {
		int n, m;
		scanf("%d %d", &n, &m);
		TrieNode* trie = readInput(n);
		int result = 0;
		for (int i = 0; i < m; ++i) {
			char str[11];
			scanf("%s", str);
			result += countKeys(trie, str);
		}
		printf("%d\n", result+m-1);
	}
	return 0;
}