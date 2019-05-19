#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>

using namespace std;

string s = "moo";
string res[30];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	res[0] = "moo";

	for (int i = 1; i < 26; ++i)
	{
		res[i] += res[i - 1];
		res[i] += "m";
		for (int j = 0; j < i + 2; ++j)
			res[i] += "o";
		res[i] += res[i - 1];
	}

	int len25 = res[25].length();
	int len26 = len25 * 2 + 29;
	int len27 = len26 * 2 + 30;

  	int n;
	cin >> n;

	if(n<=len25)
		cout << res[25][n - 1] << '\n';
	else if (n > len25 && n <= len25 + 29)
	{
		if (n == len25 + 1)
			cout << "m";
		else
			cout << "o";
	}
	else if (n <= len26)
	{
		n -= len25;
		n -= 29;
		cout << res[25][n - 1];
	}
	else if (n > len26 && n <= len26 + 30)
	{
		if (n == len26 + 1)
			cout << "m";
		else
			cout << "o";
	}
	else if (n <= len27)
	{
		n -= len26;
		n -= 30;

		if (n <= len25)
			cout << res[25][n - 1] << '\n';

		else if (n > len25 && n <= len25 + 29)
		{
			if (n == len25 + 1)
				cout << "m";
			else
				cout << "o";
		}
		else if (n <= len26)
		{
			n -= len25;
			n -= 29;
			cout << res[25][n - 1];
		}
	}


	

	

	return 0;
}