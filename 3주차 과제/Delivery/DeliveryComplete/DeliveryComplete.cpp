#include <iostream>
#include <algorithm>
using namespace std;

// ���� ���� ����
// �Է¹��� ���� ����޴� �迭, �� ���� �����ϴ� �迭
// �׸��� �� ���� Ž���ϸ鼭 �� ���� �����ϴ� dp �迭
int input[3001] = { 0, };
int sum_input[3001] = { 0, };
int dp[3001] = { 0, };

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// �Է��� �޴´�.
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> input[i];
	}

	int truck, helicopter;
	cin >> truck >> helicopter;

	// ����
	sort(input + 1, input + 1 + N);

	// �κ���
	for (int i = 1; i <= N; i++) {
	//	cout << input[i] << "\n";
		sum_input[i] = sum_input[i - 1] + input[i];
	}

	// ��� (DP �̿�, �ð����⵵�� O(n^2)�̾�� �Ѵ�.
	// �ð����⵵�� O(n^3)�� ��� �ð� �ʰ�!
	for (int i = 1; i <= N; i++) {
		int answer;
		// �տ����� ����� �Ǿ� �ִ� ���¿���,
		// �� input�� Ʈ������ �̿��ϴ� ���
		answer = dp[i - 1] + input[i] * truck;
		
		// �︮���͸� ���� ���
		// �� ���� �ݴ��(�ڿ�������) Ž���� �� ����
		for (int j = i; j > 0; j--) {
			int part_answer = dp[j - 1] + helicopter;
			int mid = (j + i) / 2;

			// �ð� �ʰ��� ���ƾ� �Ѵ�.
			// for���� �ϳ� ���ּ�, O(n^3)�� O(n^2)���� ������
			/*
			// ��ü
			for (int k = j; k <= i; k++) {
				int temp2 = (input[mid] - input[k]) * truck;
				if (temp2 < 0) temp2 *= -1;
				part_answer += temp2;
			}

			// ����� �߽����� ����
			for (int k = j; k < mid; k++) {
				int temp2 = (input[mid] - input[k]) * truck;
				part_answer += temp2;
			}

			// ����� �߽����� ������
			for (int k = mid+1; k <= i; k++) {
				int temp2 = (input[k] - input[mid]) * truck;
				part_answer += temp2;
			}
			*/

			// �κ����� �̿��ؼ� ���� ����� ���⿡ ���´�.
			int left_sum = (input[mid] * (mid - j + 1) - (sum_input[mid] - sum_input[j-1])) * truck;
			int right_sum = ((sum_input[i] - sum_input[mid - 1]) - (input[mid] * (i - mid + 1))) * truck;
			part_answer += left_sum;
			part_answer += right_sum;
		//	cout << left_sum << "\n";
		//	cout << right_sum << "\n";
			if (answer > part_answer) answer = part_answer;
		//  cout << part_answer << "\n";
		//  cout << answer << "\n";
		}
		dp[i] = answer;
	//  cout << dp[i] << "\n";
	}

	cout << dp[N];
	return 0;
}