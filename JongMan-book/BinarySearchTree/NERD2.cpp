#include <iostream>
#include <map>
using namespace std;

map<int, int> coords; // ���� �ٸ� ���� ��������� �ʴ� ���� ���

bool IsDominated(int x, int y) {
    // x���� �����ʿ� �մ� �� �� ���� ���ʿ� �ִ� ���� ã��
    map<int, int>::iterator it = coords.lower_bound(x);
    // �׷� ���� ���ٸ� (x, y)�� ��������� ����
    if (it == coords.end()) return false;
    // (x, y)�� ������� ����Ƿ��� �� ������ ����Ǿ���.
    return y < it->second;
}

void RemoveDominated(int x, int y) {
    map<int, int>::iterator it = coords.lower_bound(x);
    // (x, y)���� ���ʿ� �ִ� ���� ����
    if (it == coords.begin()) return;
    // �ݺ��� �Һ��� : it�� (x, y) �ٷ� ���ʿ� �ִ� ��
    --it;
    while (true) {
        // it�� ǥ���ϴ� ���� (x, y)�� ������� ������ ���� ����
        if (it->second > y) break;
        // ���� ���� �����Ƿ� it�� ����� ����
        if (it == coords.begin()) {
            coords.erase(it);
            break;
        }
        // ���� ������ ���ͷ����͸� �ϳ� �Űܳ��� it�� ����
        else {
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}

// ���� (x, y)�� �߰��Ǿ�����, coords�� �����ϰ� �ٸ� ���� ��������� �ʴ� ���� ���� ��ȯ
int Registered(int x, int y) {
    // (x, y)�� ������Ѵٸ� (x, y)�� ����
    if (IsDominated(x, y)) return coords.size();
    // ������ �ִ� �� �� (x, y)�� ������ϴ� ���� ����
    RemoveDominated(x, y);
    coords[x] = y;
    return coords.size();
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, sum = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int _x, _y;
            cin >> _x >> _y;
            sum += Registered(_x, _y);
        }
        cout << sum << '\n';
    }
    return 0;
}