#include <iostream>
#include <stack>
using namespace std;

bool WellMatched(const string& fomula) {
    const string opening("({["), closing(")}]");
    stack<char> openStack;
    for (int i = 0; i < fomula.size(); ++i) {
        if (opening.find(fomula[i]) != -1) // 여는 괄호면 스택에 저장
            openStack.push(fomula[i]);
        else { // 닫는 괄호일 때
            if (openStack.empty()) return false; // 여는 괄호가 없다면
            if (opening.find(openStack.top()) != closing.find(fomula[i])) // 괄호끼리 짝이 맞지 않다면
                return false;
            openStack.pop(); // 괄호 한쌍 없앰
        }
    }
    return openStack.empty();
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        string str;
        cin >> str;
        if (WellMatched(str))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}