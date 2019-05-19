#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int a[1001];
int p[1001];
int lis[1001];

int max_position = 0;
int max_i = 0;

void print_answer(int max_i, int max_position);

int main(void)
{
	int N;	// 수열 N의 크기
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> a[i];

	lis[0] = -99999;
	for (int i = 0; i <= N; i++)
		lis[1] = 99999;

	int k = 1;
	for (int i = 1; i <= N; i++) {
		int positions = std::lower_bound(lis, lis + k, a[i]) - lis + 1;
		//cout << "positions = " << positions << endl;
		p[i] = positions - 1;
		if (max_position < p[i]) {
			max_position = p[i];
			max_i = i;
		}
		lis[p[i]] = a[i];
		//cout << "lis[p[i]] = " << lis[p[i]] << endl;
		if (k == p[i]) k++;
	}

	//cout << "max_position = " << max_position << endl;
	//cout << "max_i = " << max_i << endl;
	cout << max_position << endl; // 가장 긴 증가하는 부분 수열의 길이
	print_answer(max_i, max_position);
	/*
	// DEBUG
	cout << "input\n";
	for (int i = 1; i <= N; i++)
		cout << a[i] << " ";
	cout << "\n\n";

	cout << "P\n";
	for (int i = 1; i <= N; i++)
		cout << p[i] << " ";
	cout << "\n\n";

	cout << "LIS\n";
	for (int i = 1; i < k; i++)
		cout << lis[i] << " ";
	cout << "\n\n";
	*/

	return 0;
}

void print_answer(int max_i, int max_position)
{
	//cout << "max_i = " << max_i << ", max_position = " << max_position << endl;
	int j = max_i - 1;
	int pos = max_position - 1;
	if (pos == -1) return;
	while (1) {
		if (p[j] == pos) {
			break;
		}
		//	cout << "p[" << j << "]=" << p[j] << endl;
		//	cout << "pos = " << pos << endl;
		j--;
	}
	print_answer(j, pos);
	cout << a[max_i] << " ";
}