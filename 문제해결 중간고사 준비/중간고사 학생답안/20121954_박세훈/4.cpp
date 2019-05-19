#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int lightAmount, colorAmount;
int light[];
int lightsiman[];
int result;
int main() {
	int maxindex = 0;
	scanf("%d%d", &lightAmount,&colorAmount);
	for (int i = 0; i < lightAmount; i++) {
		scanf("%d", light[i]);
	}
	maxindex=simantric(lightAmount);
	checkChange(maxindex);
}
int simantric(int len) {
	int maxindex = 0;
	for (int i = 1; i<len-1 ; i++) 
	{
		for (int j = 1; j < len / 2 + 1; j++) 
		{
			if (i - j<0 || i + j>len) {
				break;
			}
			else if (light[i - j] == light[i + j]) {
				lightsiman[i]++;
			}
		}
		maxindex = max(maxindex, lightsiman[i]);
	}
	return maxindex;
}
void checkChange(int maxindex) {
	int a = lightAmount - maxindex;
	if (a > maxindex) {
		for (int i = 0; i < a; i++) {
			if (light[maxindex] != light[maxindex + i]) {
				result++;
			}
		}
	}
	else {
		for (int i = 0; i < maxindex; i++) {
			if (light[maxindex] != light[maxindex - i]) {
				result++;
			}
		}
	}
}