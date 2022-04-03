#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> GetPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0); // pi[i] = N[……i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이
    // KMP로 자기 자신을 찾음.
    // N에서 N을 찾음. begin = 0 이면 자기자신이니 안됨.
    int begin = 1, matched = 0;
    // 비교할 분자가 N의 끝에 도달할 때까지 찾으면서 부분일치를 모두 기록
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
    vector<int> pi = GetPartialMatch(N); // pi[i] = N[……i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이
    int begin = 0, matched = 0; // i = 0부터 시작
    while (begin <= n - m) {
        // 만약 짚더미에 해당 글자가 바늘의 해당글자와 같다면
        if (matched < m && H[begin + matched] == N[matched]) {
            ++matched;
            if (matched == m) ret.push_back(begin);
        }
        else {
            // 예외 : matched가 0인경우 다음칸부터 계속 탐색
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

int Shift(const string& original, const string& target) { // 환형시프트 함수
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