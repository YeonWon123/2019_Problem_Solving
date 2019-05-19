#pragma warning(disable:4996)
#include <iostream>
#include <array>
using namespace std;
int found(int count, int countSum);

int N;
array<char, 10000000000> moo;

int main(void)
{
	scanf("%d", &N);

	moo.at(0) = 'm';
	moo.at(1) = 'o';
	moo.at(2) = 'o';

	found(0, 3);

	printf("%c", moo.at(N - 1));

	return 0;
}

int found(int count, int countSum)
{
	moo.at(countSum) = 'm';
	for (int i = countSum + 1; i < countSum + count + 4; i++)
		moo.at(i) = 'o';
	for (int i = 0; i < countSum; i++)
		moo.at(i + countSum + count + 4) = moo.at(i);

	if (countSum >= N)
		return 0;
	found(count + 1, countSum * 2 + count + 4);
}