// 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "algorithm"
#include "queue"
using namespace std;

struct q {
	int sum;
	int another;
	int depth;
	bool in;
	q(int a, int b, int c, bool d) {
		sum = a; another = b; depth = c; in = d;
	}
};

int main()
{
	int T, k;
	cin >> T >> k;
	int* ar = new int[100*1000];
	int count = 0;
	int sum = 0;
	for (int i = 0; i < k;i++) {
		int coin, number;
		cin >> coin >> number;
		for (int j = 0; j < number;j++) {
			ar[count++] = coin;
			sum += coin;
		}
	}
	sort(ar, ar + count);
	reverse(ar, ar + count);
	queue<q> a;
	a.push(q(0,sum, 0, true));
	int answer = 0;
	while (!a.empty()) {
		q temp = a.front();
		a.pop();
		if (temp.depth + 1 == count) {
			if (temp.sum + ar[temp.depth] == T) {
				answer++;
			}
		}
		else if (temp.another + temp.sum >= T && temp.sum<=T) {
			if (temp.sum == T) {
				answer++;
			}
			else {
				if (temp.in || !(ar[temp.depth] == ar[temp.depth - 1])) {
					a.push(q(temp.sum + ar[temp.depth], temp.another - ar[temp.depth], temp.depth + 1, true));
				}
				a.push(q(temp.sum, temp.another - ar[temp.depth], temp.depth + 1, false));
			}
		}
	}
	cout << answer;
    return 0;
}