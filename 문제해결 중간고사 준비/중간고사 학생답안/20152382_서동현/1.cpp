#include <iostream>
using namespace std;

int N;
int start = 3;
long long length = 3;

void dividecon(int left, int right, int length, int start);

int main()
{
	cin >> N;

	while (length <= N) {
		start++;
		length = length * 2 + (start);
	}

	//cout << (length - start) / 2 << endl;

	if (N <= (length - start) / 2) {
		dividecon(0, (length - start) / 2, (length - start) / 2, start - 1);
	}
	else if (N >= ((length - start) / 2 + start)) {
		dividecon((length - start) / 2 + start, length, (length - start) / 2, start - 1);
	}
	else {
		int ans = N - ((length - start) / 2);
		if (ans == 1) {
			cout << "m" << endl;
		}
		else {
			cout << "o" << endl;
		}


	}

	return 0;
}

void dividecon(int left, int right, int length, int start)
{
	if (length == 3) {
		if (N == left) {
			cout << "o" << endl;
		}
		else {
			cout << "m" << endl;
		}
		return;
	}

	if (N <= (length - start) / 2) {
		dividecon(0, (length - start) / 2, (length - start) / 2, start - 1);
	}
	else if (N > ((length - start) / 2 + start)) {
		dividecon((length - start) / 2 + start, length, (length - start) / 2, start - 1);
	}
	else {
		int ans = N - ((length - start) / 2);
		if (ans == 1) {
			cout << "m" << endl;
		}
		else {
			cout << "o" << endl;
		}
		return;

	}




}
