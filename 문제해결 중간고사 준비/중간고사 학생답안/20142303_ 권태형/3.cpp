
#include<iostream>
#include<vector>
using namespace std;

//<price, num>
vector<pair<int, int>> board;
vector<int> cache;
int exchangePrice, coinNum;
int main() {
	cin >> exchangePrice;
	cache = vector<int>(exchangePrice+1, 0);
	cache[0] = 1;
	cin >> coinNum;
	board = vector<pair<int, int>>(coinNum);
	for (int i = 0; i < coinNum; i++) {
		int tempPrice, tempNum;
		cin >> tempPrice;
		cin >> tempNum;
		board[i] = make_pair(tempPrice, tempNum);
	}

	for (int tempCoin = 0; tempCoin < coinNum; tempCoin++) {
		for(int tempPrice = exchangePrice; tempPrice>=0;tempPrice--){
			for (int tempCoinNum = 1; tempCoinNum <= board[tempCoin].second; tempCoinNum++) {
				if (tempCoinNum*board[tempCoin].first > tempPrice) {
					break;
				}
				cache[tempPrice] += cache[tempPrice - tempCoinNum*board[tempCoin].first];
			}
		}
	}
	cout << cache[exchangePrice] << endl;
}