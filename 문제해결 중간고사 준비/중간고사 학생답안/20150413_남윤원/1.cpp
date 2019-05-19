#include <iostream>
using namespace std;

void moo_print(int N);

string moo = " ";

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	
	int size = 3;
	int i;
	for (i = 0; size < N; i++) {
		size = 2 * size + (i + 4);
	//	cout << size << endl;
	}

	moo_print(i);

	cout << moo[N];
	return 0;
}

void moo_print(int N)
{
	if (N == 0) {
		moo += "moo";
		//cout << "moo";
		return;
	}

	moo_print(N - 1);

	moo += "m";
	//cout << "m";
	for (int i = 1; i <= N + 2; i++) {
		moo += "o";
		//cout << "o";
	}
	moo_print(N - 1);
}