#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void Init(vector<int> box, vector<int>& psum, int k) {
    psum.push_back(0);
    psum.push_back(box[0]%k);
    for (int i = 1; i < box.size(); ++i)
        psum.push_back((box[i]+psum[i])%k);
}

int WaysToBuy(const vector<int>& psum, int k) {
    const int MOD = 20091101;
    int ret = 0;
    // psum[]의 중복된 각 값을 기록
    vector<long long> count(k, 0);
    for (int i = 0; i < psum.size(); ++i)
        count[psum[i]]++;
    // 중복값이 2이상이면 경우의 수를 구함
    for (int i = 0; i < k; ++i)
        if (count[i] >= 2)
            ret = (ret+((count[i]*(count[i]-1))/2))%MOD;
    return ret;
}

int MaxBuys(const vector<int>& psum, int k) {
    // ret[i] = 첫번째 상자에서 i번째 상자까지 고려했을때 살 수 잇는 최대 갯수
    vector<int> ret(psum.size(), 0);
    // psum[s] = psum[i]를 만족하는 s의 마지막 위치
    vector<int> prev(k, -1);
    for (int i = 0; i < psum.size(); ++i) {
        // i번째 상자를 고려하지 않는 경우
        if (i > 0) ret[i] = ret[i-1];
        else ret[i] = 0;
        // psum[i]를 전에도 본 적이 있다면 prev[psum[i]]+1부터 여기까지 쭉 사봄
        int loc = prev[psum[i]];
        if (loc != -1) ret[i] = max(ret[i], ret[loc]+1);
        prev[psum[i]] = i;
    }
    return ret.back();
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        vector<int> box, psum;
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            int input;
            cin >> input;
            box.push_back(input);
        }
        Init(box, psum, k);
        cout << WaysToBuy(psum, k) << ' ';
        cout << MaxBuys(psum, k) << '\n';
    }
    return 0;
}