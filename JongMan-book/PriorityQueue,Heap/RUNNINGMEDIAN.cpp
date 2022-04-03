#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

struct RNG {
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) { }
    int Next() {
        int ret = seed;
        seed = ((seed * (long long)a) + b) % 20090711;
        return ret;
    }
};

int RunningMedian(int n, RNG rng) {
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int ret = 0;
    // 1. maxHeap의 크기는 minHeap의 크기와 같거나 1더 큼
    // 2. maxHeap.pop() <= minHeap.pop()
    for (int cnt = 1; cnt <= n; ++cnt) {
        // 우선 1번 불변식부터 만족시킴
        if (maxHeap.size() == minHeap.size()) maxHeap.push(rng.Next());
        else minHeap.push(rng.Next());
        // 2번 불변식이 깨졌을 경우 복구함
        if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, a, b;
        cin >> n >> a >> b;
        RNG rng(a, b);
        cout << RunningMedian(n, rng) << '\n';
    }
    return 0;
}