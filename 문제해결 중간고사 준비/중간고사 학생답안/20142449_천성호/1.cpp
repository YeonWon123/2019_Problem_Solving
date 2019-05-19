#include <cstdio>

int dp[100];

void rec(int input, int level) {
//	printf("\ninput = %d level = %d\n", input, level);
	if (level == 0) {
//		printf("level 0\n");
		if (input == 1) printf("%c", 'm');
		else printf("%c", 'o');
		return;
	}
	if (input <= dp[level - 1]) {
//		printf("front\n");
		rec(input, level - 1);
	}
	else if (input <= dp[level-1] + 3) {
//		printf("middle\n");
		int tmp = input - dp[level - 1];
		if (tmp == 1) {
			printf("%c", 'm');
		}
		else printf("%c", 'o');
		return;
	}
	else {
//		printf("back\n");
		rec(input - dp[level-1] - level - 3, level-1);
	}
	
}


int main(void) {

	int input;
	scanf("%d", &input);
	if (input <= 3) {
		if (input == 1) printf("%c", 'm');
		else printf("%c", 'o');
		return 0;
	}


	dp[0] = 3;
	int i;
	for (i = 1; i < 100; ++i) {
		dp[i] = dp[i - 1] * 2 + i + 3;
//		printf("%d = %d\n", i, dp[i]);
		if (dp[i] > input) {
			break;
		}
	}

	rec(input, i);

	return 0;
}