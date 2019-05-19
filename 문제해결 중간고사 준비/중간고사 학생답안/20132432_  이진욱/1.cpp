#include <iostream>
#include <string>
#include<algorithm>
#include <stdlib.h>

using namespace std;

string div_con(int k);

string moo = "moo";
string o = "o";

int N;
int k;

string div_con(int k) {

		string now;
		string temp;
		string result;
		int div;
	
		div = k-1;
		now = moo;

	for (int i = 0; i < k; i++)
		now += o;

	if (k == 0) {
		return moo;
	}
	else {

		temp = div_con(div);

		result = temp + now;

		temp = div_con(div);

		result = result + temp;

		return result;
	}
}

int main() {

	int seq = 0;
	string ans;

	cin >> N;
	
	k = 0;

	while (seq < N) {
		seq = seq * 2 + (k + 3);
		k++;
	}
	ans = div_con(k);


	cout << ans[N - 1] << endl;


}




