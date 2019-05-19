#include<iostream>
using namespace std;
pair <int, int> coin[];
int a,b;
int result;
int main() {
	
	scanf("%d", &a);
	scanf("%d", &b);
	for (int i = 0; i < b; i++) {
		int j = 0;
		scanf("%d%d",coin[i].first,coin[i].second );
	}
	biggerNum(b);
	setting(a, coin[0].first, coin[0].second, 0);

}
void biggerNum(int num) {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (coin[i].first < coin[j].first) {
				pair <int, int> init;
				init = coin[i];
				coin[i] = coin[j];
				coin[j] = init;
			}
		}
	}
}
void setting(int dev,int value,int amount,int index) {
	int i = 0,j=0;
	i = dev / value;
	j = dev % value;
	if (i > amount) {
		setting(dev - value*amount, coin[index + 1].first, coin[index + 1].second,index+1);
	}
	else if (i < amount&&j > 0) {
		for (int k = 0; k < amount; k++)
		{
			setting(dev-value*k , coin[index + 1].first, coin[index + 1].second, index + 1);
		}
	}

	if (j == 0 && i == 0) {
		result++;
	}
	else {
		return;
	}
}