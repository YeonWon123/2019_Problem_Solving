#include <iostream>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin >> N;

	int last = 2 * N - 1;

	for (int i = N; i >= 1; i--) {
		for (int j = 1; j <= (last - (2 * i - 1)) / 2; j++)
			printf(" ");

		for (int j = 1; j <= 2 * i - 1; j++)
			printf("*");

		printf("\n");
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j <= (last - (2*i-1))/2; j++)
			printf(" ");

		for (int j = 1; j <= 2*i-1; j++)
			printf("*");

		if (i != N)
			printf("\n");
	}
}