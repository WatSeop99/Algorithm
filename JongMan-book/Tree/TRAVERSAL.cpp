#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> Slice(const vector<int>& v, int a, int b) {
    return vector<int>(v.begin() + a, v.begin() + b);
}

void PrintPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
    const int N = preorder.size(); // Ʈ���� ���Ե� ��� ��
    if (preorder.empty()) return; // �� �� Ʈ����� ����.
    const int root = preorder[0];
    const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin(); // ���� ����Ʈ���� ũ��
    const int R = N - 1 - L; // ������ ����Ʈ���� ũ��
    // ����, ������ ��� �� ��Ʈ ���
    PrintPostOrder(Slice(preorder, 1, L + 1), Slice(inorder, 0, L));
    PrintPostOrder(Slice(preorder, L + 1, N), Slice(inorder, L + 1, N));
    cout << root << ' ';
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        int n;
        vector<int> preorder, inorder;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int input;
            cin >> input;
            preorder.push_back(input);
        }
        for (int i = 0; i < n; ++i) {
            int input;
            cin >> input;
            inorder.push_back(input);
        }
        PrintPostOrder(preorder, inorder);
        cout << '\n';
    }
    return 0;
}