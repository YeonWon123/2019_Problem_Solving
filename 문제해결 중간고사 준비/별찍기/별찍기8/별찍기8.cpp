#include <iostream>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin >> N;

	int last = 2 * N - 1;
	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= i; k++)
			printf("*");

		for (int k = 1; k <= (last - (2*i-1))/2; k++)
			printf("  ");

		for (int k = 1; k <= i; k++)
			printf("*");
			
		printf("\n");
	}

	for (int i = N-1; i >= 1; i--) {
		for (int k = 1; k <= i; k++)
			printf("*");

		for (int k = 1; k <= (last - (2 * i - 1)) / 2; k++)
			printf("  ");

		for (int k = 1; k <= i; k++)
			printf("*");

		if (i != 1)
			printf("\n");
	}
	return 0;
}