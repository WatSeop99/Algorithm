#include <iostream>
#include <vector>
#include <string>
using namespace std;

string Reverse(string::iterator& it) {
	char head = *(it++);
	if(head == 'b' || head == 'w') return string(1, head);
	string uperLeft = Reverse(it);
	string uperRight = Reverse(it);
	string lowerLeft = Reverse(it);
	string lowerRight = Reverse(it);
	// 각각 위와 앨 조각들의 위치를 바꿈.
	return string("x")+lowerLeft+lowerRight+uperLeft+uperRight;
}

int main(void) {
	int c;
	cin >> c;
	for(int tc = 0; tc < c; ++tc) {
		string qTree;
		cin >> qTree;
		string::iterator iter = qTree.begin();
		cout << Reverse(iter) << endl;
	}
	
	return 0;
}