#include <iostream>
using namespace std;

int main(void)
{
	int N;
	cin >> N;

	int last = 2 * N - 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= (last - (2 * i - 1)) / 2; j++) {
			printf(" ");
		}

		printf("*");

		if (i == 1) {
			printf("\n");
			continue;
		}

		for (int j = 2; j <= i; j++) {
			printf(" ");
			printf("*");
		}

		printf("\n");
	}
}