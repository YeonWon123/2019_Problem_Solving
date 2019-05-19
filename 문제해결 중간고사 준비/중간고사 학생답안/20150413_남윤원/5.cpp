#include <iostream>
using namespace std;

//#define DEBUG

typedef struct POINT {
	int start_y;
	int start_x;
	int end_y;
	int end_x;
} point;

double dp[101][101];
point nogo[101];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N, M;
	cin >> N >> M;

	int K;
	cin >> K;

	for (int i = 1; i <= K; i++) {
		cin >> nogo[i].start_x >> nogo[i].start_y >> nogo[i].end_x >> nogo[i].end_y;
		if (nogo[i].start_x > nogo[i].end_x) {
			int temp = nogo[i].start_x;
			nogo[i].start_x = nogo[i].end_x;
			nogo[i].end_x = temp;
		}

		if (nogo[i].start_y > nogo[i].end_y) {
			int temp = nogo[i].start_y;
			nogo[i].start_y = nogo[i].end_y;
			nogo[i].end_y = temp;
		}
	}

	// dp 배열 초기화, 단, j 또는 i가 0이면 1
	dp[0][0] = 1;
	for (int j = 0; j <= M; j++) {
		for (int i = 0; i <= N; i++) {
			if (i == 0 && j == 0) {
				dp[0][0] = 1;
				continue;
			}

			if (i == 0 && j != 0) {
				// 우선 자기 앞에 도로가 공사를 해서, 자신에게 올 게 없는 상황일 경우 0
				if (dp[j - 1][i] == 0) {
					dp[j][i] = 0;
					continue;
				}

				// 자신 위에 있는 도로와 자신의 도로가 공사중이면 안됨!
				bool isNogo = false;
				for (int p = 1; p <= K; p++) {
					if (nogo[p].start_y == j - 1 && nogo[p].start_x == i && nogo[p].end_y == j && nogo[p].end_x == i) {
						dp[j][i] = 0;
						isNogo = true;
						break;
					}
				}
				if (isNogo == false) {
					dp[j][i] = 1;
				}
			}
			else if (j == 0 && i != 0) {
				// 우선 자기 앞에 도로가 공사를 해서, 자신에게 올 게 없는 상황일 경우 0
				if (dp[j][i-1] == 0) {
					dp[j][i] = 0;
					continue;
				}
				// 자신 위에 있는 도로와 자신의 도로가 공사중이면 안됨!
				bool isNogo = false;
				for (int p = 1; p <= K; p++) {
					if (nogo[p].start_y == j && nogo[p].start_x == i - 1 && nogo[p].end_y == j && nogo[p].end_x == i) {
						dp[j][i] = 0;
						isNogo = true;
						break;
					}
				}
				if (isNogo == false) {
					dp[j][i] = 1;
				}
			}
			else
				dp[j][i] = 0;
		}
	}

	// 초기화 완료
#ifdef DEBUG
	cout << "\nnogo출력\n";
	for (int p = 1; p <= K; p++) {
		cout << nogo[p].start_y << " " <<  nogo[p].start_x << " " << nogo[p].end_y << " " << nogo[p].end_x << "\n";
	}

	cout << "\ndp출력\n";
	for (int j = 0; j <= M; j++) {
		for (int i = 0; i <= N; i++) {
			cout << dp[j][i] << " ";
		}
		cout << "\n";
	}
#endif

	// dp 배열 채우기
	// 단, 공사중인 구간은 피하기
	// 점화식 : dp[j][i] = dp[j-1][i] + dp[j][i-1]
	for (int j = 1; j <= M; j++) {
		for (int i = 1; i <= N; i++) {

			// dp[j-1][i]를 더할 수 있는가?
			// 자신 이전에 있는 도로와 자신의 도로가 공사중이면 안됨!
			bool isNogo = false;
			for (int p = 1; p <= K; p++) {
				if (nogo[p].start_y == j - 1 && nogo[p].start_x == i && nogo[p].end_y == j && nogo[p].end_x == i) {
#ifdef DEBUG
					cout << j - 1 << " " << i << "와 " << j << " " << i << "는 공사중인 도로!\n";
#endif
					isNogo = true;
					break;
				}
			}
			if (isNogo == false) {
				dp[j][i] += dp[j-1][i];
			}
			
			// dp[j][i-1]을 더할 수 있는가?
			isNogo = false;
			for (int p = 1; p <= K; p++) {
#ifdef DEBUG
				if (j == 9 && i == 12) {
					cout << (nogo[p].start_y == j) << (nogo[p].start_x == i - 1) << (nogo[p].end_y == j) << (nogo[p].end_x == i) << endl;
				}
#endif

				if (nogo[p].start_y == j && nogo[p].start_x == i - 1 && nogo[p].end_y == j && nogo[p].end_x == i) {
#ifdef DEBUG
					cout << j << " " << i-1 << "와 " << j << " " << i << "는 공사중인 도로!\n";
#endif

					isNogo = true;
					break;
				}
			}
			if (isNogo == false) {
				dp[j][i] += dp[j][i-1];
			}
		}
	}

#ifdef DEBUG
	cout << "\n최종 dp출력\n";
	for (int j = 0; j <= M; j++) {
		for (int i = 0; i <= N; i++) {
			cout << dp[j][i] << " ";
		}
		cout << "\n";
	}
#endif
	cout << dp[M][N];
	return 0;
}