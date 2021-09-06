#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXINT = numeric_limits<int>::max();

struct RMQ {
    int n; // �迭�� ����
    vector<int> rangeMin; // �� ������ �ּ�ġ

    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        Init(array, 0, n - 1, 1);
    }

    int Init(const vector<int>& array, int left, int right, int node) {
        if (left == right) return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = Init(array, left, mid, node * 2);
        int rightMin = Init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    int Query(int left, int right, int node, int nodeLeft, int nodeRight) {
        // �� ������ ��ġ�� ������ ���� ū ���� ��ȯ : ���õ�
        if (right < nodeLeft || nodeRight < left) return MAXINT;
        // node�� ǥ���ϴ� ������ array[left...right]�� ������ ���ԵǴ� ���
        if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
        // ���� ���� ������ Ǭ �ڿ� ��ħ
        int mid = (nodeLeft + nodeRight) / 2;
        return min(Query(left, right, node * 2, nodeLeft, mid), Query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int Query(int left, int right) {
        return Query(left, right, 1, 0, n - 1);
    }

    int Update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        // index�� ��尡 ǥ���ϴ� ������ ������� ��� ������
        if (index < nodeLeft || nodeRight < index) return rangeMin[node];
        // Ʈ���� �������� ������ ���
        if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(Update(index, newValue, node * 2, nodeLeft, mid), Update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }

    int Update(int index, int newValue) {
        return Update(index, newValue, 1, 0, n - 1);
    }
};

const int MAX_N = 100000;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N]; // Ʈ���� ��ȣ�� �Ϸù�ȣ ������ ��������
int locInTrip[MAX_N], depth[MAX_N]; // �� ��尡 trip�� ó�� �����ϴ� ��ġ, �׸��� �� ����� ����
int nextSerial; // ���� �Ϸù�ȣ

void Traverse(int here, int d, vector<int>& trip) {
    // Traverse()�� ó�� �湮���ڸ��� �Ϸù�ȣ�� �ο���
    // �̷��� �ϸ� �׻� �θ�� �ڼպ��� ���� �Ϸù�ȣ�� ���Ե�
    no2serial[here] = nextSerial;
    serial2no[nextSerial] = here;
    ++nextSerial;
    // ���̰��
    depth[here] = d;
    // trip�� �������� �Ϸù�ȣ�� �߰���
    locInTrip[here] = trip.size();
    trip.push_back(no2serial[here]);
    // ��� �ڽĳ�� �湮
    for (int i = 0; i < child[here].size(); ++i) {
        Traverse(child[here][i], d + 1, trip);
        // �ڽĳ�带 �湮�ϰ� ������� ���ƿ� ������ �ٽ� �߰��ϱ�
        trip.push_back(no2serial[here]);
    }
}

RMQ* PrepareRMQ() {
    nextSerial = 0;
    // ��ȸ�������� ������ ����� �Ϸù�ȣ�� ����
    vector<int> trip;
    Traverse(0, 0, trip);
    return new RMQ(trip);
}

int Distance(RMQ* rmq, int u, int v) {
    // trip[]�迭���� u�� v�� ù ������ġ�� ã��
    int lu = locInTrip[u], lv = locInTrip[v];
    if (lu > lv) swap(lu, lv);
    // rmq�� u�� v�� �ּ� ���� ������ �Ϸù�ȣ�� ��ȯ��
    int lca = serial2no[rmq->Query(lu, lv)];
    return depth[u] + depth[v] - 2 * depth[lca];
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        for (int i = 0; i < MAX_N; ++i)
            child[i].clear();
        int n, q;
        cin >> n >> q;
        vector<int> temp;
        for (int i = 1; i < n; ++i) {
            int parents;
            cin >> parents;
            child[parents].push_back(i);
        }
        RMQ* rmq = PrepareRMQ();
        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << Distance(rmq, a, b) << '\n';
        }
    }
    return 0;
}