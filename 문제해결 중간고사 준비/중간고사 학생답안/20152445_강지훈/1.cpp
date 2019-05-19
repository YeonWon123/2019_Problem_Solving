#include <iostream>
using namespace std;

int x;
char result;
int moo(int n, int p) {

	if (n == 0) {
		x+= 3;
		return 3;
	}
	int a = moo(n - 1,p);
	x += n + 3;
	int b = moo(n - 1,p);

	return a + b + mid;
}

int main() {
	int n;
	cin >> n;
	moo(n,n);



	return 0;
}