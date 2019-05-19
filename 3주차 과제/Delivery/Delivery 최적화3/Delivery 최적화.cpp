#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
//#define DEBUG
using namespace std;

// ��ǰ�� �ִ� ������, ���� �����̸� �� ������ �����ϴ� ����ü ����
typedef struct polong_count {
	long polong;
	long counts;

} POlong_COUNT;

// ���� ����
vector<POlong_COUNT> arr;
vector<POlong_COUNT> accu;
long truck, helicopter;
long *dp_answer;

// �Լ� ����
bool compare(POlong_COUNT a, POlong_COUNT b);

int main(void)
{
	// �Է��� �޴� �κ�
	long N;
	cin >> N;

	arr.push_back({ 0, 0 });
	long temp;
	long sw = 0;
	long flag;
	for (long i = 1; i <= N; i++) {
		cin >> temp;
		flag = 0;
		for (long j = 1; j < i - sw; j++) {
			if (temp == arr[j].polong) {
				arr[j].counts++;
				flag = 1;
				sw++;
				break;
			}
		}
		if (flag == 0) arr.push_back({ temp, 1 });
	}

	sort(arr.begin() + 1, arr.end(), compare);

	accu.push_back({ 0, 0 });
	accu.push_back({ arr[1].polong * arr[1].counts, arr[1].counts });
	for (long i = 2; i < arr.size(); i++)
		accu.push_back({ arr[i].polong * arr[i].counts + accu[i - 1].polong, arr[i].counts + accu[i - 1].counts });
#ifdef DEBUG
	for (long i = 1; i < arr.size(); i++)
		cout << arr[i].polong << " " << arr[i].counts << "\n";
#endif
	cin >> truck >> helicopter;

	// ����ϴ� �κ�
	// DP�� �̿��Ͽ� �ذ��� ����. �켱 �迭�� ���� �Ҵ�
	dp_answer = new long[arr.size()];


	// �տ������� ���������� Ž���� ������.
	// �ù� �������� 10�� ���� ��, 10�̶� 20�� ���� ��, 10�̶� 20�̶� 40�� ���� ��, ...
	for (long i = 1; i < arr.size(); i++) {
#ifdef DEBUG
		cout << i << "\n";
#endif
		// ���� �ʱ�ȭ
		long mid = 0;
		long mid2 = 0;
		long answer = 1000000000;
		long truck_only = 0;

		// �ù� �������� �ϳ��� �ִٸ�, Ʈ���� ������ �︮���Ͱ� ������ �����ؼ�
		// dp_answer �迭�� �� �տ� ����
		if (i == 1) {
			truck_only = arr[i].polong * arr[i].counts * truck;
			answer = (truck_only > helicopter ? helicopter : truck_only);
			dp_answer[i] = answer;
#ifdef DEBUG
			cout << answer << "\n";
#endif
			continue;
		}

		// �ù� �������� �� ���� �ִٸ�
		// 1. �︮���͸� ���� ���� �ʴ� ���
		// 2. �︮���͸� 1�븸 ���� ���
		// 3. �︮���͸� 2�� ���� ���
		// �׷��� dp�� �̿��ϸ� �̹� ù ������������ �������� ���������ϱ�
		// �� ��° �������� �ִ� �ù踦 ��� �������� �ű������ ������ �ȴ�.

		// ���� �� ��° �������� �ִ� �ù踦 Ʈ���� �̿��� ���
		// �� �� �տ��� ����� ��(���� �������� �ִ� �ù踦 �������� ����� ��)�� ������
		answer = arr[i].polong * arr[i].counts * truck + dp_answer[i - 1];
#ifdef DEBUG
		cout << answer << "\n";
#endif
		// �︮���͸� ����ϴ� ��츦 ������ ����.
		// �� ��� �ڿ������� Ž���� �ϸ� ������ ������ �������� ����� �� �ִ�.(DP)
		for (long j = i; j > 0; j--) {
			long part_answer;
			if (j == 1) part_answer = 0;
			else part_answer = dp_answer[j - 1];
			// �︮���͸� ���� �� ���� �����
			// ������ �߰� ������ �︮���͸� ���� �δ� ���̴�.
			// ���� �߰� ������ �ش��ϴ� ��ǥ�� ���� ������.
			// mid = (arr[j].polong + arr[i].polong) / 2;
			mid = arr[(j + i) / 2].polong;
			mid2 = (j + i) / 2;

			// �︮���͸� Ÿ�� �� ������ Ʈ������ �ű�� �� ����ϱ�
			part_answer += helicopter;
			// mid2 �߽����� ����
			long left = ((mid * (accu[mid2].counts - accu[j - 1].counts)) - (accu[mid2].polong - accu[j - 1].polong)) * truck;
			part_answer += left;

			/*for (long k = j; k < mid2; k++) {
				long temp2 = ((mid - arr[k].polong) * arr[k].counts * truck);
				part_answer += temp2;
			}*/

			long right = ((accu[i].polong - accu[mid2 - 1].polong) - (mid * (accu[i].counts - accu[mid2 + 1].counts))) * truck;
			// mid2 �߽����� ������
			part_answer += right;
			/*
			for (long k = mid2 + 1; k <= i; k++) {
				long temp2 = ((mid - arr[k].polong) * arr[k].counts * truck);
				temp2 = (temp2 > 0) ? temp2 : temp2 * (-1);
				part_answer += temp2;
			}*/
			// ������ ��(�ּڰ�)���� ���ϱ�
#ifdef DEBUG
			cout << "left: " << left << "\n";
			cout << "right: " << right << "\n";
			cout << part_answer << "\n";
#endif
			if (answer > part_answer) answer = part_answer;
		}
#ifdef DEBUG
		cout << "dp_answer : " << answer << "\n";
#endif
		// �� for���� ������ i-1��° �������� �ִ� �ù� + i��° �������� �ִ� �ù���� ���ؼ�
		// �������� �����Ƿ� �� ���� dp_answer[i]�� ����
		dp_answer[i] = answer;
	}

	// ���� ������� dp_answer���� �� �ڿ� ������.
	cout << dp_answer[arr.size() - 1];
	return 0;
}

bool compare(POlong_COUNT a, POlong_COUNT b) {
	// polong�� �� ���� ������ �����ϱ�!
	return a.polong < b.polong;
}