#include <iostream>

using namespace std;

int main(void)
{
	int arrSize = 3;
	int originSize = 0;
	int i = 4;
	int N;
	bool m = false;

	
	cin >> N;

	if (N < arrSize)
		if (N == 1)
			m = true;

	while (N > arrSize)
	{
		originSize = arrSize;
		if (originSize + 1 == N)
			m = true;

		arrSize = arrSize * 2 + i;
		if (arrSize - originSize + 1 == N)
			m = true;

		i++;
	}
	
	if (m == false)
		cout << "o";
	else
		cout << "m";

	return 0;
}