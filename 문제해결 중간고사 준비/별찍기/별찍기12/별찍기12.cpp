#include <iostream>
using namespace std;

int main(void)
{
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = N; j > i; j--) {
			printf(" ");
		}

		for (int j = 1; j <= i; j++) {
			printf("*");
		}

		printf("\n");
	}

	for (int i = N-1; i >= 1; i--) {
		for (int j = N; j > i; j--) {
			printf(" ");
		}

		for (int j = 1; j <= i; j++) {
			printf("*");
		}

		printf("\n");
	}
}