#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

int N;
char S[1000000001];
int k = 0;
int slen = 3;

void Moo();

int main(void)
{
	scanf("%d", &N);

	S[0] = 'm';
	S[1] = 'o';
	S[2] = 'o';
	S[3] = 0;

	Moo();

	printf("%c\n", S[N-1]);

	return 0;
}

void Moo()
{
	int tmplen = slen;

	if (slen < N) {
		k++;
		S[slen] = 'm';
		for (int i = 0; i < (k + 2); i++) {
			slen++;
			S[slen] = 'o';
		}

		for (int i = 0; i < tmplen; i++) {
			slen++;
			S[slen] = S[i];
		}
		slen++;
		S[slen] = 0;

		Moo();

		return;
	}
	else {
		return;
	}
}