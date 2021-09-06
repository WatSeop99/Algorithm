#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXINT = numeric_limits<int>::max();

struct RMQ {
    int n; // 배열의 길이
    vector<int> rangeMin; // 각 구간의 최소치

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
        // 두 구간이 겹치지 않으면 아주 큰 값을 반환 : 무시됨
        if (right < nodeLeft || nodeRight < left) return MAXINT;
        // node가 표현하는 범위가 array[left...right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
        // 양쪽 구간 나눠서 푼 뒤에 합침
        int mid = (nodeLeft + nodeRight) / 2;
        return min(Query(left, right, node * 2, nodeLeft, mid), Query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int Query(int left, int right) {
        return Query(left, right, 1, 0, n - 1);
    }

    int Update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        // index가 노드가 표현하는 구간과 상관없는 경우 무시함
        if (index < nodeLeft || nodeRight < index) return rangeMin[node];
        // 트리의 리프까지 내려온 경우
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
int no2serial[MAX_N], serial2no[MAX_N]; // 트리의 번호와 일련번호 사이의 대응관계
int locInTrip[MAX_N], depth[MAX_N]; // 각 노드가 trip에 처음 등장하는 위치, 그리고 각 노드의 깊이
int nextSerial; // 다음 일련번호

void Traverse(int here, int d, vector<int>& trip) {
    // Traverse()가 처음 방문하자마자 일련번호를 부여함
    // 이렇게 하면 항상 부모는 자손보다 작은 일련번호를 갖게됨
    no2serial[here] = nextSerial;
    serial2no[nextSerial] = here;
    ++nextSerial;
    // 깊이계산
    depth[here] = d;
    // trip에 현재노드의 일련번호를 추가함
    locInTrip[here] = trip.size();
    trip.push_back(no2serial[here]);
    // 모든 자식노드 방문
    for (int i = 0; i < child[here].size(); ++i) {
        Traverse(child[here][i], d + 1, trip);
        // 자식노드를 방문하고 현재노드로 돌아올 때까지 다시 추가하기
        trip.push_back(no2serial[here]);
    }
}

RMQ* PrepareRMQ() {
    nextSerial = 0;
    // 순회과정에서 만나는 노드의 일련번호를 담음
    vector<int> trip;
    Traverse(0, 0, trip);
    return new RMQ(trip);
}

int Distance(RMQ* rmq, int u, int v) {
    // trip[]배열에서 u와 v의 첫 출현위치를 찾음
    int lu = locInTrip[u], lv = locInTrip[v];
    if (lu > lv) swap(lu, lv);
    // rmq는 u와 v의 최소 공동 조상의 일련번호로 반환함
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