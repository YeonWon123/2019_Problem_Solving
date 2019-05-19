// 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int* light = new int[N];
	cin >> light[0];
	int count = 0;
	for (int i = 1; i < N;i++) {
		int temp;
		cin >> temp;
		if (temp != light[count]) {
			light[++count] = temp;
		}
	}
	bool** palindrome = new bool*[count+1];
	for (int i = 0; i < count + 1;i++) {
		palindrome[i] = new bool[i+1];
	}
	for (int i = 0; i < count + 1;i++) {
		for (int j = 0; j <= i;j++) {
			if (light[i] == light[j])
				palindrome[i][j] = true;
			else
				palindrome[i][j] = false;
		}
	}
	int middle = count / 2;
	int start = middle - 1;
	int finish = middle + 1;
	int answer = 0;
	while (start >= 0 && finish <= count) {
		if (start == -1) {
			answer += count - finish + 1;
			break;
		}
		if (finish == count + 1) {
			answer += start + 1;
			break;
		}
		if (palindrome[start][finish]) {
			answer++;
		}
		else {
			answer += 2;
		}
		start--;
		finish++;
	}
	cout << answer;
    return 0;
}