#include <iostream>
#include <deque>

#define MAXVALUE 0
struct xType {
	xType() { }
	xType(int _x1, int _y1, int _x2, int _y2) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}

	int x1, y1;
	int x2, y2;
};

int findx(std::deque<xType> xlist,int i, int j) {	//from left is 1 down is 2
	int returnValue = 0;
	for (int k = 0; k < (int)xlist.size(); k++) {
		if (xlist.at(k).x2 == i && xlist.at(k).y2 == j) {
			if (xlist.at(k).x1 == xlist.at(k).x2) {
				if (returnValue != 0)
					returnValue = 3;
				else {
					returnValue = 1;
				}
			}
			else {
				returnValue = 2;
			}
		}
	}

	return returnValue;
}
void showMap(int map[][101], int n, int m) {
	for (int j = m; j >= 0; j--) {
		for (int i = 0; i <=n; i++) {
			std::cout << map[i][j] << "\t";
		}
		std::cout << std::endl;
	}

}
void processXmap(xType& tmp) {
	int tmpx, tmpy;
	if (tmp.x1 < tmp.x2 || tmp.y1 < tmp.y2) {
		return;
	}
	else {
		tmpx = tmp.x1;
		tmpy = tmp.y1;
		tmp.x1 = tmp.x2;
		tmp.y1 = tmp.y2;
		tmp.x2 = tmpx;
		tmp.y2 = tmpy;
	}
}
int main()
{
	int xMap[101][101] = { 0, };
	int map[101][101] = { 0, };
	std::deque<xType> xlist;
	int n, m;
	int xn;

	int tmp;
	xType tmpXType;


	std::cin >> n >> m >> xn;
	for (int i = 0; i < xn; i++) {
		std::cin >> tmpXType.x1 >> tmpXType.y1 >> tmpXType.x2 >> tmpXType.y2;
		processXmap(tmpXType);
		xMap[tmpXType.x2][tmpXType.y2] = 1;
		xlist.push_back(tmpXType);
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (j == 0 && i == 0)
				map[i][j] = 1;
			else if (i == 0) {
				if (xMap[i][j] == 0)
					map[i][j] = map[i][j - 1];
				else {
					map[i][j] = MAXVALUE;
				}
			}
			else if (j == 0) {
				if (xMap[i][j] == 0)
					map[i][j] = map[i - 1][j];
				else {
					map[i][j] = MAXVALUE;
				}
			}
			else {
				if (xMap[i][j]) {
					tmp = findx(xlist, i, j);
					if (tmp == 3)
						map[i][j] = MAXVALUE;
					if (tmp == 2)
						map[i][j] = map[i][j - 1];
					if (tmp == 1)
						map[i][j] = map[i - 1][j];
				}
				else {
					map[i][j] = map[i][j - 1] + map[i - 1][j] ;
				}
			}
		}
	}

	//showMap(map, n, m);
	std::cout << map[n][m];
	return 0;

}