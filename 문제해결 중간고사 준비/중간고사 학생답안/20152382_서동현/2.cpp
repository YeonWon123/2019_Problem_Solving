#include <iostream>
#include <climits>
using namespace std;

int N, M;
int seq[5002];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> seq[i];
	}
	
	int left = 0;
	int right = INT_MAX;
	int mid;
	int maxMid = INT_MAX;

	while (left <= right) {
		mid = (left + right) / 2;
		//cout << "" << endl;
		//cout << "mid: " << mid << endl;
		int sum = 0;
		int cnt = 0;
		int min = seq[0];
		int max = seq[0];
		
		for (int i = 1; i < N; i++) {
			int item = seq[i];
			//cout << "" << endl;
			//cout << "item: " << item << endl;
			if (min > item) {
				min = item;
				

			}
			if (item > max) {
				max = item;
		
			}
			//cout << "max: " << max << endl;
			//cout << "min: " << min << endl;
			//cout << "minus: " << max - min << endl;
			if (max - min > mid) {
				
				cnt++;
				//cout << "minus: over " << cnt << endl;
				min = item;
				max = item;
			}
			//cout << cnt << endl;
			
		}

		
		//cout << "cnt: " << cnt << endl;

		if (cnt+1 <= M) {
			right = mid - 1;
			if (maxMid>mid) {
				maxMid = mid;
			}
		}
		else {
			left = mid + 1;
		}
		

	}

	cout << maxMid << endl;

	return 0;
}

