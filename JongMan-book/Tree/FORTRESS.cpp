#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    vector<TreeNode*> children;
};
int longest; // 지금까지 찾은 가장 긴 잎-잎 경로의 길이를 저장
int n, y[100], x[100], radius[100]; // 입력 데이터

int Height(TreeNode* root) {
    // 각 자식을 루트로 하는 서브트리의 높이를 계산
    vector<int> heights;
    for (int i = 0; i < root->children.size(); ++i)
        heights.push_back(Height(root->children[i]));
    // 만약 자식이 없다면 0을 반환
    if (heights.empty()) return 0;
    sort(heights.begin(), heights.end());
    // root를 최상위 노드로 하는 잎-잎 경로를 고려함
    if (heights.size() >= 2)
        longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
    // 트리의 높이는 서브트리 높이의 최대치에 1을 더해 계산
    return heights.back() + 1;
}

int Sqr(int x) {
    return x * x;
}

int Sqrdist(int a, int b) {
    return Sqr(y[a] - y[b]) + Sqr(x[a] - x[b]);
}

bool Encloses(int a, int b) { // 원a가 원b를 포함하는가?
    return radius[a] > radius[b] && Sqrdist(a, b) < Sqr(radius[a] - radius[b]); // 원a가 원b를 포함할 때의 원과의 관계
}

bool IsChild(int parent, int child) {
    if (!Encloses(parent, child)) return false;
    for (int i = 0; i < n; ++i)
        // 해당 원의 자식이 바로 아래인가?(해당 원과 자식 간선 수가 1인가?)
        if (i != parent && i != child && Encloses(parent, i) && Encloses(i, child)) return false;
    return true;
}

TreeNode* GetTree(int root) {
    TreeNode* ret = new TreeNode();
    for (int ch = 0; ch < n; ++ch) // ch성벽이 root 성벽에 직접적으로 포함되어있다면 트리를 만들고 자손에 추가
        if (IsChild(root, ch)) ret->children.push_back(GetTree(ch));
    return ret;
}

int Solve(TreeNode* root) {
    longest = 0;
    int h = Height(root);
    // 트리의 높이와 최대 잎-잎 경로 길이 중 큰 것을 택함
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