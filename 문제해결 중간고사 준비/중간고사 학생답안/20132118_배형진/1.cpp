#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
vector<int> tmp;

int vsum()
{
	int ret = 0;
	for (int i : v)
		ret += i;
	return ret;
}

void make()
{
	for (int i : tmp)
		v.push_back(i);
}

int main()
{
	int n, m = 1;
	bool isMoo = false;
	scanf("%d", &n);

	int k = 3;
	v.push_back(k);

	if (n == 1) isMoo = true;

	while (m <= n) {
		m += vsum();
		tmp = v;
		v.push_back(++k);
		make();
	}

	m = 1;
	for (int i : v)
	{
		m += i;
		if (n == m) {
			isMoo = true;
			break;
		}
	}

	if (isMoo) printf("m");
	else printf("o");

	return 0;
}