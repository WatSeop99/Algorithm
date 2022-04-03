#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> GetPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0); // pi[i] = N[����i]�� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ��� �ִ� ����
    // KMP�� �ڱ� �ڽ��� ã��.
    // N���� N�� ã��. begin = 0 �̸� �ڱ��ڽ��̴� �ȵ�.
    int begin = 1, matched = 0;
    // ���� ���ڰ� N�� ���� ������ ������ ã���鼭 �κ���ġ�� ��� ���
    while (begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

vector<int> KMPSearch(const string& H, const string& N) {
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = GetPartialMatch(N); // pi[i] = N[����i]�� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ��� �ִ� ����
    int begin = 0, matched = 0; // i = 0���� ����
    while (begin <= n - m) {
        // ���� ¤���̿� �ش� ���ڰ� �ٴ��� �ش���ڿ� ���ٸ�
        if (matched < m && H[begin + matched] == N[matched]) {
            ++matched;
            if (matched == m) ret.push_back(begin);
        }
        else {
            // ���� : matched�� 0�ΰ�� ����ĭ���� ��� Ž��
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

int Shift(const string& original, const string& target) { // ȯ������Ʈ �Լ�
    return KMPSearch(original + original, target)[0];
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, rst = 0;
        bool flag = false;
        string cur, next;
        cin >> n;
        cin >> cur;
        while (n--) {
            cin >> next;
            if (flag) rst += Shift(cur, next);
            else rst += Shift(next, cur);
            cur = next;
            flag = !flag;
        }
        cout << rst << '\n';
    }

    return 0;
}