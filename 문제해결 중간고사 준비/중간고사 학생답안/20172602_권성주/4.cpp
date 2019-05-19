
#include <iostream>
#include <deque>

struct listType {
	int number;
	int list[201];

		//TODO : COPY
};

void copyFuncF(listType& list, listType copyed, int n) {
	list.number = copyed.number;

	for (int i = 0; i < n; i++) {
		list.list[i] = copyed.list[i];
	}
}

void changeColor(listType& list, int n, int colorN,int listsize) {
	int precolor;
	int point = n;
	precolor = list.list[n];
	while (precolor == list.list[point]) {
		list.list[point] = colorN;
		point++;
		if (point > listsize)
			break;
	}
}

int main()
{
	listType inputData, nowp, tmp;

	std::deque<listType> qu;
	int samecheck;
	int n, colorn;
	int smallNumber;
	int clearcheck;
	int preColor = 0;


	std::cin >> n >> colorn;
	for (int i = 0; i < n; i++) {
		std::cin >> inputData.list[i];
	}

	smallNumber = 500000;
	inputData.number = 0;
	qu.push_back(inputData);

	while (!qu.empty()) {
		clearcheck = 0;
		nowp = qu.front();
		qu.pop_front();

		if (nowp.number >= smallNumber)
			continue;

		samecheck = nowp.list[0];
		for (int i = 1; i < n; i++) {
			if (nowp.list[i] != samecheck)
				break;
			if (i == n-1) {
				clearcheck = 1;
				smallNumber = nowp.number;
			}
		}
		if (clearcheck == 1)
			continue;


		for (int i = 0; i < n; i++) {
			if (i != 0)
				if (preColor == nowp.list[i])
					continue;

			for (int j = 1; j <= colorn; j++) {
				if (nowp.list[i] == j)
					continue;
				copyFuncF(tmp, nowp,n);

				changeColor(tmp, i, j,n);
				tmp.number = tmp.number + 1;
				qu.push_back(tmp);
			}
			preColor = nowp.list[i];
				
		}
	}

	std::cout << smallNumber;
	return 0;
}
