#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    vector<TreeNode*> children;
};
int longest; // ���ݱ��� ã�� ���� �� ��-�� ����� ���̸� ����
int n, y[100], x[100], radius[100]; // �Է� ������

int Height(TreeNode* root) {
    // �� �ڽ��� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ���
    vector<int> heights;
    for (int i = 0; i < root->children.size(); ++i)
        heights.push_back(Height(root->children[i]));
    // ���� �ڽ��� ���ٸ� 0�� ��ȯ
    if (heights.empty()) return 0;
    sort(heights.begin(), heights.end());
    // root�� �ֻ��� ���� �ϴ� ��-�� ��θ� �����
    if (heights.size() >= 2)
        longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
    // Ʈ���� ���̴� ����Ʈ�� ������ �ִ�ġ�� 1�� ���� ���
    return heights.back() + 1;
}

int Sqr(int x) {
    return x * x;
}

int Sqrdist(int a, int b) {
    return Sqr(y[a] - y[b]) + Sqr(x[a] - x[b]);
}

bool Encloses(int a, int b) { // ��a�� ��b�� �����ϴ°�?
    return radius[a] > radius[b] && Sqrdist(a, b) < Sqr(radius[a] - radius[b]); // ��a�� ��b�� ������ ���� ������ ����
}

bool IsChild(int parent, int child) {
    if (!Encloses(parent, child)) return false;
    for (int i = 0; i < n; ++i)
        // �ش� ���� �ڽ��� �ٷ� �Ʒ��ΰ�?(�ش� ���� �ڽ� ���� ���� 1�ΰ�?)
        if (i != parent && i != child && Encloses(parent, i) && Encloses(i, child)) return false;
    return true;
}

TreeNode* GetTree(int root) {
    TreeNode* ret = new TreeNode();
    for (int ch = 0; ch < n; ++ch) // ch������ root ������ ���������� ���ԵǾ��ִٸ� Ʈ���� ����� �ڼտ� �߰�
        if (IsChild(root, ch)) ret->children.push_back(GetTree(ch));
    return ret;
}

int Solve(TreeNode* root) {
    longest = 0;
    int h = Height(root);
    // Ʈ���� ���̿� �ִ� ��-�� ��� ���� �� ū ���� ����
    return max(h, longest);
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> x[i] >> y[i] >> radius[i];
        TreeNode* root = GetTree(0);
        cout << Solve(root) << '\n';
    }
    return 0;
}