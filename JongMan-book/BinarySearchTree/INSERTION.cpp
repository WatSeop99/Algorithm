#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

typedef int KeyType;

struct Node {
    KeyType key;
    int priority, size;
    Node* left, * right;
    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(nullptr), right(nullptr) { }
    void SetLeft(Node* newLeft) {
        left = newLeft;
        CalcSize();
    }
    void SetRight(Node* newRight) {
        right = newRight;
        CalcSize();
    }
    void CalcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef pair<Node*, Node*> NodePair;

NodePair Split(Node* root, KeyType key) {
    if (root == nullptr) return NodePair(nullptr, nullptr);
    // 루트가 key 미만이면 오른쪽 서브트리를 쪼갬
    if (root->key < key) {
        NodePair rs = Split(root->right, key);
        root->SetRight(rs.first);
        return NodePair(root, rs.second);
    }
    // 루트가 key 이상이면 왼쪽 서브트리르 쪼갬
    NodePair ls = Split(root->left, key);
    root->SetLeft(ls.second);
    return NodePair(ls.first, root);
}

Node* Insert(Node* root, Node* node) {
    if (root == nullptr) return node;
    // node가 루트를 대체해야함. 해당 서브트리를 반으로 잘라 각각자손으로 함
    if (root->priority < node->priority) {
        NodePair splitted = Split(root, node->key);
        node->SetLeft(splitted.first);
        node->SetRight(splitted.second);
        return node;
    }
    else if (node->key < root->key) root->SetLeft(Insert(root->left, node));
    else root->SetRight(Insert(root->right, node));
    return root;
}

Node* Merge(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->priority < b->priority) {
        b->SetLeft(Merge(a, b->left));
        return b;
    }
    a->SetRight(Merge(a->right, b));
    return a;
}

Node* Erase(Node* root, KeyType key) {
    if (root == nullptr) return root;
    // root를 지우고 양 서브트리를 합친 후 반환
    if (root->key == key) {
        Node* ret = Merge(root->left, root->right);
        delete root;
        return ret;
    }
    if (key < root->key) root->SetLeft(Erase(root->left, key));
    else root->SetRight(Erase(root->right, key));
    return root;
}

Node* Kth(Node* root, int k) {
    // 왼쪽 서브트리의 크기를 우선 계산
    int leftSize = 0;
    if (root->left != nullptr) leftSize = root->left->size;
    if (k <= leftSize) return Kth(root->left, k);
    if (k == leftSize + 1) return root;
    return Kth(root->right, k - leftSize - 1);
}

int CountLessThan(Node* root, KeyType key) {
    if (root == nullptr) return 0;
    if (root->key >= key)
        return CountLessThan(root->left, key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + CountLessThan(root->right, key);
}

int n, shifted[50001]; // shifted[i] = A[i]가 왼쪽으로 몇칸 속해있는가?
int A[50001];

void Solve() {
    // 1~N까지의 숫자를 저장하는 트립을 만듬
    Node* candidates = nullptr;
    for (int i = 0; i < n; ++i)
        candidates = Insert(candidates, new Node(i + 1));
    // 뒤에서부터 A[]를 채워나감
    for (int i = n - 1; i >= 0; --i) {
        // 후보중에 이 수보다 큰 수가 larger개 있음
        int larger = shifted[i];
        Node* k = Kth(candidates, i + 1 - larger);
        A[i] = k->key;
        candidates = Erase(candidates, k->key);
    }
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> shifted[i];
        Solve();
        for (int i = 0; i < n; ++i)
            cout << A[i] << ' ';
        cout << '\n';
    }
    return 0;
}