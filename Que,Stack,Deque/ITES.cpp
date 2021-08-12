#include <iostream>
#include <queue>
using namespace std;

struct RNG { // 다음 배열 원소 생성기
    unsigned seed;
    RNG() : seed(1983) { }
    unsigned next() {
        unsigned ret = seed;
        seed = ((seed*214013u)+2531011u);
        return ret%10000+1;
    }
};

int CountRange(int n, int k) {
    RNG rng;
    queue<int> range; // 구간합 저장을 위한 큐
    int ret = 0, rangeSum = 0;
    for (int i = 0; i < n; ++i) {
        // 구간에 숫자 추가
        int newSignal = rng.next();
        rangeSum += newSignal;
        range.push(newSignal);

        // 구간합이 k를 초과하는 동안 숫자뺌
        while (rangeSum > k) {
            rangeSum -= range.front();
            range.pop();
        }
        if (rangeSum == k) ++ret; // 구간합이 k와 같다면 카운트 추가
    }
    return ret;
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n , k;
        cin >> k >> n;
        cout << CountRange(n, k) << '\n';
    }

    return 0;
}