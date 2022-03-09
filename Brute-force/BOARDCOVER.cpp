#include <iostream>
#include <vector>
using namespace std;

// 주어진 칸을 덮을 수 있는 네 가지 방법
const int CoverType [4][3][2] = {
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {1, -1}}
};

// board의 (y, x)를 type번 방법으로 덮거나, 덮었던 블록을 없앰.
// delta = 1이면 덮고, -1이면 엎었던 블록을 없앰.
// 만약 블록이 제대로 떺이지 않은 경우(게임판 밖으로 나가거나, 검은 칸을 덮을 때) false를 반환함.
bool Set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for(int i = 0; i < 3; ++i) {
		const int ny = y+CoverType[type][i][0];
		const int nx = x+CoverType[type][i][1];
		if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) ok = false;
		else if((board[ny][nx] += delta) > 1) ok = false;
	}
	return ok;
}

// board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환함.
// board[i][j] = 1 이미 덮인 칸 혹은 검은 칸.
// board[i][j] = 0 아직 덮이지 않은 칸.
int Cover(vector<vector<int>>& board) {
	// 아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾음.
	int y = -1, x = -1;
	for(int i = 0; i < board.size(); ++i) {
		for(int j = 0; j < board[i].size(); ++j) {
			if(board[i][j] == 0) {
				y = i; x = j;
				break;
			}
		}
		if(y != -1) break;
	}
	// 기저 사례: 모든 칸을 채웠으면 1을 반환함.
	if(y == -1) return 1;
	int ret = 0;
	for(int type = 0; type < 4; ++type) {
		// 만약 board[y][x]를 type 형태로 덮을 수 있으면 재귀 호출함.
		if(Set(board, y, x, type, 1))
			ret += Cover(board);
		// 덮었던 블록을 치움.
		Set(board, y, x, type, -1);
	}
	return ret;
}

int main(void) {
	int c, h, w;
	cin >> c;
	for(int tc = 0; tc < c; ++tc) {
		cin >> h >> w;
		vector<vector<int>> board(h, vector<int>(w, 0));
		int count = 0;
		for(int j = 0; j < h; ++j) {
			for(int k = 0; k < w; ++k) {
				char input; cin >> input;
				if(input == '#') {
					count += 1;
					board[j][k] = 1;
				}
			}
		}
		if((h*w-count)%3 != 0) cout << 0 << endl;
		else cout << Cover(board) << endl;
	}
	return 0;
}