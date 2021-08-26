#include <iostream>
#include <map>
using namespace std;

map<int, int> coords; // 현재 다른 점에 지배당하지 않는 점의 목록

bool IsDominated(int x, int y) {
    // x보다 오른쪽에 잇는 점 중 가장 된쪽에 있는 점을 찾음
    map<int, int>::iterator it = coords.lower_bound(x);
    // 그런 점이 없다면 (x, y)는 지배당하지 않음
    if (it == coords.end()) return false;
    // (x, y)가 어느점에 지배되려면 이 점에도 지배되야함.
    return y < it->second;
}

void RemoveDominated(int x, int y) {
    map<int, int>::iterator it = coords.lower_bound(x);
    // (x, y)보다 왼쪽에 있는 점이 없음
    if (it == coords.begin()) return;
    // 반복문 불변식 : it는 (x, y) 바로 왼쪽에 있는 점
    --it;
    while (true) {
        // it가 표시하는 점이 (x, y)에 지배되지 않으면 곧장 종료
        if (it->second > y) break;
        // 이전 점이 없으므로 it만 지우고 종료
        if (it == coords.begin()) {
            coords.erase(it);
            break;
        }
        // 이전 점으로 이터레이터를 하나 옮겨놓고 it를 지움
        else {
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}

// 새점 (x, y)가 추가되었을때, coords를 갱신하고 다른 점에 지배당하지 않는 점의 개수 반환
int Registered(int x, int y) {
    // (x, y)가 지배당한다면 (x, y)를 버림
    if (IsDominated(x, y)) return coords.size();
    // 기존에 있던 점 중 (x, y)에 지배당하는 점을 지움
    RemoveDominated(x, y);
    coords[x] = y;
    return coords.size();
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, sum = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int _x, _y;
            cin >> _x >> _y;
            sum += Registered(_x, _y);
        }
        cout << sum << '\n';
    }
    return 0;
}