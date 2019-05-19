#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

vector<int> board;
vector<vector<int>> cache;
int vectorSize, targetNum;
int getMinSize(int index, int leftGroup);
int main() {
	
	cin >> vectorSize;
	cin >> targetNum;
	board = vector<int>(vectorSize);
	cache = vector<vector<int>>(vectorSize, vector<int>(targetNum + 1, -1));
	for (int i = 0; i < vectorSize; i++) {
		cin >> board[i];
	}
	cout << getMinSize(0, targetNum) << endl;
	return 0;
}

int getMinSize(int index, int leftGroup)
{
	if (cache[index][leftGroup] != -1) {
		return cache[index][leftGroup];
	}
	if (board.size() - index == leftGroup) {
		cache[index][leftGroup] = 0;
		return 0;
	}
	int maxNum = 1, lowNum = 10000;
	if (leftGroup == 1) {
		for (int i = index; i < board.size(); i++) {
			maxNum = max(maxNum, board[i]);
			lowNum = min(lowNum, board[i]);
		}
		cache[index][leftGroup] = maxNum - lowNum;
		return cache[index][leftGroup];
	}
	int tempLow = 10000, maxAreaValue;
	for (int i = index; i < board.size() - leftGroup; i++) {
		maxNum = max(maxNum, board[i]);
		lowNum = min(lowNum, board[i]);
		maxAreaValue = max(maxNum-lowNum, getMinSize(i + 1, leftGroup - 1));
		tempLow = min(tempLow, maxAreaValue);
	}
	cache[index][leftGroup] = tempLow;
	return tempLow;
}
