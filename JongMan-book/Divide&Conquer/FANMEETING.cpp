#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

// num[]의 자릿수 올림을 처리함.
void normalize(vector<int>& num) { }

// 두 긴 자연수의 곱을 반환함.
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			c[i + j] += a[i] * b[j];
	normalize(c);
	return c;
}

// a += b * (10^k)를 구현함.
void addTo(vector<int>& a, const vector<int>& b, int k) {
	if (a.size() < b.size() + k)
		a.resize(b.size() + k);
	for (int i = 0; i < b.size(); ++i)
		a[i + k] += b[i];
	normalize(a);
}

// a -= b를 구현함. a >= b를 가정함.
void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); ++i)
		a[i] -= b[i];
	normalize(a);
}

// 두 긴 정수의 곱을 반환함.
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	// a 가 b 보다 짧을 경우 둘을 바꿈.
	if (an < bn) return karatsuba(b, a);
	// 기저 사례: a나 b가 비어 있는 경우.
	if (an == 0 || bn == 0) return vector<int>();
	// 기저 사례: a가 비교적 짧은 경우 O(n^2) 곱셈으로 변경함.
	if (an <= 50) return multiply(a, b);
	int half = an / 2;
	// a와 b를 밑에서 half 자리와 나머지로 분리함.
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	// z2 = a1 * b1
	vector<int> z2 = karatsuba(a1, b1);
	// z0 = a0 * b0
	vector<int> z0 = karatsuba(a0, b0);
	// a0 = a0 + a1; b0 = b0 + b1
	addTo(a0, a1, 0); addTo(b0, b1, 0);
	// z1 = (a0 * b0) - z0 - z2;
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	// ret = z0 + z1 * 10^half + z2 * 10^(half*2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> A(N), B(M);
	for (int i = 0; i < N; ++i)
		A[i] = (members[i] == 'M');
	for (int i = 0; i < M; ++i)
		B[M - i - 1] = (fans[i] == 'M');
	// karasuba 알고리즘에서 자리 올림은 생략함.
	vector<int> C = karatsuba(A, B);
	int allHugs = 0;
	for (int i = N - 1; i < M; ++i)
		if (C[i] == 0) ++allHugs;
	return allHugs;
}

int main() {
	int C;
	cin >> C;
	while (C--) {
		string a, b;
		cin >> a >> b;
		cout << hugs(a, b) << '\n';
	}
	return 0;
}