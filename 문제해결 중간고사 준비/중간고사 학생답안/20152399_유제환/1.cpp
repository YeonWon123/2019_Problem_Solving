#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long N;
long long prevLen;
vector<int> moo;

int main(void)
{
	cin >> N;
	moo.push_back(1);

	prevLen = 3;

	for (int i = 1; i <= N; i++) {
		int newMooStart = prevLen + 1;
		int prevMooSize = moo.size();
		moo.push_back(newMooStart);
		cout << newMooStart << endl;

		prevLen = prevLen * 2 + (i + 3);
	}

	if (find(moo.begin(), moo.end(), N) == moo.end())
		cout << "o" << endl;
	else
		cout << "m" << endl;
}