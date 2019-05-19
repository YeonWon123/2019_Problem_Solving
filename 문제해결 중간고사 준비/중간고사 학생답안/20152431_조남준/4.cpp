#include <stdio.h>

int N, K;
int light[200];
int maxch = 987654321;
int lpos;
int isch = 0;
int cnt = 0;

void lchange(int);

int main(void)
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &light[i]);
	}

	for (int i = 0; i < N; i++) {
		lchange(i);
		if (maxch > cnt) maxch = cnt;
	}

	printf("%d\n", maxch);

	return 0;
}

void lchange(int nu)
{
	int tmp = nu;
	cnt = 0;
	if (nu > 0 && nu < N) {
		int left, right;
		while (left < 0 && right >= N) {
			while (light[nu] != light[tmp]) {
				tmp++;
				if (tmp >= N) break;
			}
			right = tmp;
			tmp = nu;
			while (light[nu] != light[tmp]) {
				tmp--;
				if (tmp < 0) break;
			}
			left = tmp;

			if (left != -1) {
				for (int i = left + 1; i < right; i++) {
					light[i] = light[left];
					isch = 1;
				}
				if (isch = 1) {
					cnt++;
					isch = 0;
				}
			}

			if (left < 0 && right != N) {
				for (int i = left + 1; i < right; i++) {
					light[i] = light[right];
					isch = 1;
				}
				if (isch = 1) {
					cnt++;
					isch = 0;
				}
			}
		}
	}
	else if (nu == 0) {
		while (tmp <= N) {
			while (light[nu] != light[tmp]) {
				tmp++;
				if (tmp >= N) break;
			}
			for (int i = 0; i < tmp; i++) {
				light[i] = light[tmp];
				isch = 1;
			}
			if (isch == 1) {
				cnt++;
				isch = 0;
			}
		}
	}
	else if (nu == N) {
		while (tmp >= 0) {
			while (light[nu] != light[tmp]) {
				tmp--;
				if (tmp < 0) break;
			}
			for (int i = nu; i >= 0; i--) {
				light[i] = light[tmp];
				isch = 1;
			}
			if (isch == 1) {
				cnt++;
				isch = 0;
			}
		}
	}
}