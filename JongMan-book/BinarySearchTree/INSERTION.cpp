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
    // ��Ʈ�� key �̸��̸� ������ ����Ʈ���� �ɰ�
    if (root->key < key) {
        NodePair rs = Split(root->right, key);
        root->SetRight(rs.first);
        return NodePair(root, rs.second);
    }
    // ��Ʈ�� key �̻��̸� ���� ����Ʈ���� �ɰ�
    NodePair ls = Split(root->left, key);
    root->SetLeft(ls.second);
    return NodePair(ls.first, root);
}

Node* Insert(Node* root, Node* node) {
    if (root == nullptr) return node;
    // node�� ��Ʈ�� ��ü�ؾ���. �ش� ����Ʈ���� ������ �߶� �����ڼ����� ��
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
    // root�� ����� �� ����Ʈ���� ��ģ �� ��ȯ
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
    // ���� ����Ʈ���� ũ�⸦ �켱 ���
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

int n, shifted[50001]; // shifted[i] = A[i]�� �������� ��ĭ �����ִ°�?
int A[50001];

void Solve() {
    // 1~N������ ���ڸ� �����ϴ� Ʈ���� ����
    Node* candidates = nullptr;
    for (int i = 0; i < n; ++i)
        candidates = Insert(candidates, new Node(i + 1));
    // �ڿ������� A[]�� ä������
    for (int i = n - 1; i >= 0; --i) {
        // �ĺ��߿� �� ������ ū ���� larger�� ����
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