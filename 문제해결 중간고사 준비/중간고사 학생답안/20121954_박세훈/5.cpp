#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
struct road {
	int preX;
	int preY;
	int curX;
	int curY;
};
int result=1;
int xdir[3] = { -1,0,1 };
int ydir[2] = { 0,1 };
int N, M;
int num;
road emptyRoad[];
int main() {
	scanf("%d%d", &N, &M);
	scanf("%d", num);
	for (int i = 0; i < num; i++) {
		scanf("%d%d%d%d", emptyRoad[i].preX, emptyRoad[i].preY, emptyRoad[i].curX, emptyRoad[i].curY);
	}
	roadExplore(0, 0, num);
	printf("%d", result);
}
void roadExplore(int y,int x,int empty) {
	int possibleRoad = 0;
	bool checkEmpty = true;
	if (y < N || x < M) {
		for (int i = 0; i < 2; i++)
		{
			int ny = ydir[i] + y;
			for (int j = 0; j < 3; j++)
			{
				int nx = xdir[j] + x;
				for (int k = 0; k < empty; k++)
				{
					if (y == emptyRoad[k].preY&&x == emptyRoad[k].preX&&nx == emptyRoad[k].curX&&ny == emptyRoad[k].curY)
					{
						checkEmpty = false;
						break;
					}
				}
				if (!checkEmpty) {
					roadExplore(ny, nx, empty);
					possibleRoad++;
				}
			}
		}
	}
	result = possibleRoad*result;
}