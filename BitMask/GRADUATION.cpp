#include <iostream>
#include <algorithm>
#include <cstring>
#include <intrin.h>
using namespace std;

const int INF = 987654321;
int n, k, m, l;
int prereguisite[12]; // 선수과목 집합
int classes[10]; // 학기에 개설되는 수업 집합
int cache[10][12]; // 메모이제이션용 캐쉬

void Init() {
    memset(prereguisite, 0, sizeof(prereguisite));
    memset(classes, 0, sizeof(classes));
    for (int i = 0; i < 10; ++i)
        memset(cache[i], -1, sizeof(int)*12);
}

int Graduate(int semester, int taken) {
    if (__popcnt(taken) >= k) return 0; // k과목 이상을 들었다면 못들음
    if (semester == m) return INF; // 학기가 다 지나면 수업 듣는게 불가
    // 메모이제이션
    int& ret = cache[semester][taken];
    if (ret != -1) return ret;
    ret = INF;
    int canTaken = (classes[semester] & ~taken); // 이번학기 과목에서 들었던 과목을 삭제
    for (int i = 0; i < n; ++i)
        if ((canTaken & (1 << i)) && (taken & prereguisite[i]) != prereguisite[i]) // 해당과목을 들을 수 있지만, 선수과목을 못들었다면
            canTaken &= ~(1 << i); // 들을 수 있는 과목에서 해당 과목 삭제
    // 부분집합 순회(들을 수 있는 과목에서 하나씩 삭제하면서)
    for (int take = canTaken; take > 0; take = (take-1) & canTaken) {
        if (__popcnt(take) > l) continue; // 한학기에 최대한 들을 수 있는 과목 수를 넘어가면 넘어감.
        ret = min(ret, Graduate(semester+1, take | taken)+1); // 해당 과목 들었을때 비교
    }
    ret = min(ret, Graduate(semester+1, taken)); // 해당과목 못들었을때 비교
    return ret;
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        Init();
        cin >> n >> k >> m >> l;
        for (int i = 0; i < n; ++i) { // prerequisite 셋팅
            int num;
            cin >> num;
            for (int j = 0; j < num; ++j) {
                int cl;
                cin >> cl;
                prereguisite[i] |= (1 << cl);
            }
        }
        for (int i = 0; i < m; ++i) { // classes 셋팅
            int num;
            cin >> num;
            for (int j = 0; j < num; ++j) {
                int clInSm;
                cin >> clInSm;
                classes[i] |= (1 << clInSm);
            }
        }
        int rst = Graduate(0, 0);
        if (rst != INF)
            cout << rst << '\n';
        else
            cout << "IMPOSSIBLE" << '\n';
    }
    return 0;
}