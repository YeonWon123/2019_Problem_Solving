#include<iostream>
#include<vector>
using namespace std;
int num;
string b;
string a;
int main() {
	
	scanf("%d", &num);
	makeSentence(0);
}
string makeSentence(int n) {
	string pre;
	if (a[n] != '\0') {
		printf("%c", a[n]);
		return a;
	}
	if (n == 0) {
		pre = "moo";
	}
	else {
		pre[n + 2] = 'o';
	}
	b =pre+ "moo";
	a = b + makeSentence(n + 1);

}