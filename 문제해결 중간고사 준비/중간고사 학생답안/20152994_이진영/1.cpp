#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;

int N;
int len;
string s = "moo";
string pre;
string mid = "moo";
vector<int> mid_sz;
vector<int> pre_sz;

char moo(int n, int k) {
	string temp = "moo";
	while (true) {
		if (n <= s.length())
			break;
		else {
			pre =  s;
			temp.append("o");
			s.append(temp);
			s.append(pre);
			len = s.length();
			k += 1;
		}
	}
	return s[n - 1];
}


int main() {
	cin >> N;

	moo(N, 0);

	cout << s[N-1];

	return 0;
}