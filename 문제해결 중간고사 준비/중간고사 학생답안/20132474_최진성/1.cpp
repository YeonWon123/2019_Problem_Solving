#include <cstdio>
#include <cstring>
using namespace std;

int n;
int pos=3;
char str[1000000010];

void moo(int size, int count) {
	str[pos++] = 'm';
	for (int i = 0; i < count+2; i++) {
		str[pos++] = 'o';
		if (pos > n) return;
	}

	for (int i = 0; i < size; i++) {
		str[pos++] = str[i];
		if (pos > n) return;
	}

	moo(size*2+count+3, count + 1);
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);

	scanf("%d", &n);

	str[0] = 'm';
	str[1] = 'o';
	str[2] = 'o';

	moo(3, 1);

	printf("%c", str[n-1]);

	return 0;
}