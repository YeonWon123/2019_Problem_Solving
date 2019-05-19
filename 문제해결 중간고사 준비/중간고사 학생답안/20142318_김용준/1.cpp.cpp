// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str("moo");
	int n;
	long long size = 3;
	int i = 1;
	string temp;
	string temp2 = "";
	cin >> n;

	while (size < n) {
		temp = "m";
		temp2 = "";
		temp2 = str;
		for (int j = 0; j < i + 2; j++) {
			temp += "o";
		}
		size = size + size + i++ + 3;
		str += temp;
		str += temp2;
	}
	
	cout << str[n - 1];
    return 0;
}

