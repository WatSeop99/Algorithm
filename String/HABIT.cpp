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
        // ù t���ڰ� �ٸ��� �̵��� �̿��� ��
        if (group[a] != group[b]) return group[a] < group[b];
        // �ٸ��ٸ� S[a+t...]�� S[b+t...]�� ù t���ڸ� ��
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
    vector<int> perm(n); // ��������� ���̻�迭�� �� ��ȯ��. �� �迭�� lg(n)�� ����
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    while (t < n) {
        // group[]�� ù t���� �������� ���. ù 2t���� �������� �ٽ� ����
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        // 2t���ڰ� n�� �Ѿ�� ���̻� �迭�� �ϼ���Ŵ.
        t *= 2;
        if (t >= n) break;
        // 2t���ڸ� �������� �� �׷� ������ ����.
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

int CommonPrefix(const string& s, int i, int j) { // �������λ��� �ִ���̸� ���
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