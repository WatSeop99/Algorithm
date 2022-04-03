#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Comparator {
    const vector<int> group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) { }
    bool operator()(int a, int b) {
        // 첫 t글자가 다르면 이들을 이용해 비교
        if (group[a] != group[b]) return group[a] < group[b];
        // 다르다면 S[a+t...]와 S[b+t...]의 첫 t글자를 비교
        return group[a + t] < group[b + t];
    }
};

vector<int> GetSuffixArray(const string& s) {
    int n = s.size();
    int t = 1;
    vector<int> group(n + 1);
    for (int i = 0; i < n; ++i)
        group[i] = s[i];
    group[n] = -1;
    vector<int> perm(n); // 결과적으로 접미사배열이 될 반환값. 이 배열을 lg(n)번 정렬
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    while (t < n) {
        // group[]은 첫 t글자 기준으로 계산. 첫 2t글자 기준으로 다시 정렬
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        // 2t글자가 n을 넘어가면 접미사 배열을 완성시킴.
        t *= 2;
        if (t >= n) break;
        // 2t글자를 기준으로 한 그룹 정보를 만듬.
        vector<int> newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (compareUsing2T(perm[i - 1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i - 1]];
        }
        group = newGroup;
    }
    return perm;
}

int CommonPrefix(const string& s, int i, int j) { // 공통접두사의 최대길이를 계산
    int k = 0;
    while (i < s.size() && j < s.size() && s[i] == s[j]) {
        ++i; ++j; ++k;
    }
    return k;
}

int LongestFrequent(int k, const string& s) {
    vector<int> a = GetSuffixArray(s);
    int ret = 0;
    for (int i = 0; i + k <= s.size(); ++i)
        ret = max(ret, CommonPrefix(s, a[i], a[i + k - 1]));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c;
    cin >> c;
    while (c--) {
        int k;
        string s;
        cin >> k >> s;
        cout << LongestFrequent(k, s) << '\n';
    }

    return 0;
}