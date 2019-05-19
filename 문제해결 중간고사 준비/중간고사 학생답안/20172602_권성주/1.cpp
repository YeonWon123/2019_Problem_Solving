
#include <iostream>

#define DEFAULT_MOO_LEN 3
#define DEFAULT_MOO moo

char solve(int n) {
	int reapNum;
	int moo_len, rec_len = 0;

	if (n == 1)
		return 'm';
	else if (n <= 2)
		return 'o';
	reapNum = 0;
	moo_len = DEFAULT_MOO_LEN;
	while (moo_len < n) {
		reapNum++;
		rec_len = moo_len;
		moo_len = moo_len * 2 + reapNum + 3;
	}

	if (rec_len + reapNum + 2 < n) {
		n = n - (rec_len + reapNum + 3);
		return solve(n);
	}
	else {
		if (rec_len + 1 == n)
			return 'm';
		else {
			return 'o';
		}
	}
}

int main()
{
	
	int n;
	std::cin >> n;

	std::cout << solve(n);

	return 0;
}

