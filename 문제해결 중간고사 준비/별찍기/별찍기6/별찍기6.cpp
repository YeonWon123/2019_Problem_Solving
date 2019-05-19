#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int last = 2 * N - 1;
	for (int i = N; i >= 1; i--) {
		for (int k = 1; k <= ((last - (2 * i - 1)) / 2); k++)
			printf(" ");

		for (int k = 1; k <= 2 * i - 1; k++)
			printf("*");

		if (i != 1)
			printf("\n");
	}
	return 0;
}