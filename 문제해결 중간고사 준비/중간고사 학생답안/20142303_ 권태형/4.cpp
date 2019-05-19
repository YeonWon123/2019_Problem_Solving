
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> lamps;
int lampNum, colortype, inputTemp;
int lowChange();
bool isAllSame();
int main() {
	ios_base::sync_with_stdio(false);
	cin >> lampNum;
	cin >> colortype;
	cin >> inputTemp;
	lamps.push_back(inputTemp);
	for (int i = 1; i < lampNum; i++) {
		cin >> inputTemp;
		if (lamps[lamps.size() - 1] != inputTemp) {
			lamps.push_back(inputTemp);
		}
	}
	cout << lowChange() << endl;
}

int lowChange()
{
	if (isAllSame()) {
		return 0;
	}
	int tempSwich = lampNum*colortype;
	int tempNum, sameStart = 0, sameEnd = 0;
	for (int i = 0; i + 1 < lamps.size(); i++) {
		tempNum = lamps[i];
		if (tempNum != lamps[i + 1]) {
			for (int j = sameStart; j <= sameEnd; j++) {
				lamps[j] = lamps[i + 1];
			}
			tempSwich = min(tempSwich, 1 + lowChange());
			for (int j = sameStart; j <= sameEnd; j++) {
				lamps[j] = tempNum;
			}
			sameStart = i + 1;
			sameEnd = sameStart;
		}
		else {
			sameEnd++;
		}
	}
	return tempSwich;
}

bool isAllSame()
{
	for (int i = 0; i < lamps.size(); i++) {
		if (lamps[0] != lamps[i]) {
			return false;
		}
	}
	return true;
}
