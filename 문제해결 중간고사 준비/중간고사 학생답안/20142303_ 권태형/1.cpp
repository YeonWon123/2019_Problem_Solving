
#include <iostream>
#include <vector>
using namespace std;

int TargetNum;
vector<int> lencache;
int main()
{
	cin >> TargetNum;
	TargetNum = TargetNum;
	lencache.push_back(3);
	int tempLen = lencache[lencache.size() - 1];
	while (true)
	{
		//overtheindex
		if (tempLen< TargetNum) {
			//in middle point
			if(TargetNum - tempLen <= 4+ lencache.size() - 1){
				if (TargetNum - tempLen == 1) {
					cout << 'm' << endl;
					return 0;
				}
				else {
					cout << 'o' << endl;
					return 0;
				}
			}
			//in third place
			else if (TargetNum - tempLen - (4 + lencache.size() - 1) < tempLen) {
				TargetNum -= (tempLen + (4 + lencache.size() - 1));
			}
			//we have made more then
			else {
				tempLen = tempLen * 2 + 4 + lencache.size() - 1;
				lencache.push_back(tempLen);
			}
		}
		else if (tempLen >= TargetNum) {
			if (TargetNum == 1) {
				cout << 'm' << endl;
				return 0;
			}
			else {
				cout << 'o' << endl;
				return 0;
			}
		}
	}
	return 0;
}
