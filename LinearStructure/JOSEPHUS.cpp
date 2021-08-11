#include <iostream>
#include <list>
using namespace std;

void Josephus(int n, int k) {
    list<int> survivors; // 생존자 리스트
    for (int i = 1; i <= n; ++i)
        survivors.push_back(i);
    list<int>::iterator kill = survivors.begin(); // 죽일사람을 가리키는 iterator
    while (n > 2) {
        // 첫번째 사람을 죽임
        kill = survivors.erase(kill); // erase는 원소 삭제 후 다음 원소를 가리킴
        if (kill == survivors.end())
            kill = survivors.begin();
        --n;
        for (int i = 0; i < k-1; ++i) {
            ++kill;
            if (kill == survivors.end())
                kill = survivors.begin();
        }
    }
    cout << survivors.front() << ' ' << survivors.back() << '\n';
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, k;
        cin >> n >> k;
        Josephus(n, k);
    }

    return 0;
}