// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "algorithm"
#include "string"
using namespace std;

int main()
{
	int N;
	cin >> N;
	string s = "moo";
	string o = "ooo";
	while (s.length()<N) {
		s = s + "m" + o + s;
		o += "o";
	}
	cout << s[N-1];
    return 0;
}