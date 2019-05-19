#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
#define Max 1000000
int k[Max];
int solve(int cnt,int ans);
int main() {
	int n;
	cin >> n;
	int len = n / 2;
	k[0] = 3;
	for (int i =0; i < Max; i++)
		k[i + 1] = 2 * k[i] + (i+1) + 3;
	if (n < 10) {
		string str = "moomooomoo";
		cout << str[n - 1]<<endl;
	}
	
	else {
		for (int i = 0; i < Max; i++)
			if (n >= k[0] && n <= k[i]) {
				//printf("k:%d\n", i);
				solve(i, n);
				break;
			}
	}

}
int solve(int cnt,int ans) {
	int j = 0;
	//int ccc = 0;
	string s = "moo";
	string space = "m";
	
		while (j < cnt) {
			
			//s += " ";
			if (j == 0) {
				for (int i = 0; i <=2; i++) {
					space.append("o");

				}
			}
			else {
				space.append("o");
			}
			s = s + space + s;
			j++;
		}
		
	
	//
	//cout << s <<ans<< endl;
	//for(int i=0;i<=11;i++)
	cout << s[ans - 1] << endl;
	//printf("´ä: %c\n", s[ans-1]);
	return 0;
}