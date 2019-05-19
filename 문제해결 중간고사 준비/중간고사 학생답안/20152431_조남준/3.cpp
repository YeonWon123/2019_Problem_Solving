#include <stdio.h>

int T;
int k;
int p[101], n[101];
int cnt;
int tmp;

void coin(int);

int main(void)
{
	scanf("%d", &T);
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		scanf("%d %d", &p[i], &n[i]);
	}

	coin(0);

	printf("%d\n", cnt);

	return 0;
}

void coin(int now)
{
	if (tmp >= T) return;
	for (int i = now; i < k; i++) {
		for (int j = n[i]; j > 0; j--) {
			tmp += p[i] * j;
			if (tmp != T && (i+1) < k) coin(i + 1);
			else if (tmp == T) {
				if (now == 0) tmp = p[i] * j;
				cnt++;
			}
			tmp -= p[i] * j;
		}
	}
}