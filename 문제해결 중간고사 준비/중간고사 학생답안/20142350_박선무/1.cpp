#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;

string moo[51];
//vector<char> moo;

void make_moo(int i)
{
	if (i == 25) return;
	if (i == 0) moo[i] = "moo";
	else
	{
		moo[i] = moo[i - 1] + "m";
		for (int j = 0; j < i+2; j++)
		{
			moo[i] += "o";
		}
		moo[i] += moo[i - 1];
	}
	make_moo(i + 1);
}
int main()
{
	//freopen("input.txt", "r", stdin);//다하고 무조건 주석

	int in;
	cin >> in;
	make_moo(0);
	cout << moo[24][in-1] << endl;

	//cout << "hello world" << endl;
}
