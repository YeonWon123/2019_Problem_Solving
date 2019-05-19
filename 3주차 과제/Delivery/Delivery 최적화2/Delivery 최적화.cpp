#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define DEBUG
using namespace std;

// ��ǰ�� �ִ� ������, ���� �����̸� �� ������ �����ϴ� ����ü ����
typedef struct point_count {
	int point;
	int counts;

} POINT_COUNT;

// ���� ����
vector<POINT_COUNT> arr;
vector<POINT_COUNT> accu;
int truck, helicopter;
int *dp_answer;

// �Լ� ����
bool compare(POINT_COUNT a, POINT_COUNT b);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// �Է��� �޴� �κ�
	int N;
	cin >> N;
	arr.reserve(N);

	int temp;
	int sw = 0;
	int flag;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		flag = 0;
		for (int j = 0; j < i - sw; j++) {
			if (temp == arr[j].point) {
				arr[j].counts++;
				flag = 1;
				sw++;
				break;
			}
		}
		if (flag == 0) arr.push_back({ temp, 1 });
	}

	sort(arr.begin(), arr.end(), compare);

	accu.push_back({ arr[0].point * arr[0].counts, arr[0].counts });
	for (int i = 1; i < arr.size(); i++)
		accu.push_back({ arr[i].point * arr[i].counts + accu[i - 1].point, arr[i].counts + accu[i - 1].counts });
#ifdef DEBUG
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i].point << " " << arr[i].counts << "\n";
#endif
	cin >> truck >> helicopter;

	// ����ϴ� �κ�
	// DP�� �̿��Ͽ� �ذ��� ����. �켱 �迭�� ���� �Ҵ�
	dp_answer = new int[arr.size()];


	// �տ������� ���������� Ž���� ������.
	// �ù� �������� 10�� ���� ��, 10�̶� 20�� ���� ��, 10�̶� 20�̶� 40�� ���� ��, ...
	for (int i = 0; i < arr.size(); i++) {
#ifdef DEBUG
		cout << i << "\n";
#endif
		// ���� �ʱ�ȭ
		int mid = 0;
		int mid2 = 0;
		int answer = 1000000000;
		int truck_only = 0;

		// �ù� �������� �ϳ��� �ִٸ�, Ʈ���� ������ �︮���Ͱ� ������ �����ؼ�
		// dp_answer �迭�� �� �տ� ����
		if (i == 0) {
			truck_only = arr[i].point * arr[i].counts * truck;
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
		answer = arr[i].point * arr[i].counts * truck + dp_answer[i - 1];
#ifdef DEBUG
		cout << answer << "\n";
#endif
		// �︮���͸� ����ϴ� ��츦 ������ ����.
		// �� ��� �ڿ������� Ž���� �ϸ� ������ ������ �������� ����� �� �ִ�.(DP)
		for (int j = i; j > -1; j--) {
			int part_answer;
			if (j == 0) part_answer = 0;
			else part_answer = dp_answer[j - 1];
			// �︮���͸� ���� �� ���� �����
			// ������ �߰� ������ �︮���͸� ���� �δ� ���̴�.
			// ���� �߰� ������ �ش��ϴ� ��ǥ�� ���� ������.
			// mid = (arr[j].point + arr[i].point) / 2;
			mid = arr[(j + i + 1) / 2].point;
			mid2 = (j + i + 1) / 2;

			// �︮���͸� Ÿ�� �� ������ Ʈ������ �ű�� �� ����ϱ�
			part_answer += helicopter;
			// mid2 �߽����� ����
			int left;
			if (mid2 == 0) left = 0;
			else if (j == 0) left = ((mid * accu[mid2 - 1].counts) - accu[mid2 - 1].point) * truck;
			else left = ((mid * (accu[mid2 - 1].counts - accu[j - 1].counts)) - (accu[mid2 - 1].point - accu[j - 1].point)) * truck;
			part_answer += left;

			/*for (int k = j; k < mid2; k++) {
				int temp2 = ((mid - arr[k].point) * arr[k].counts * truck);
				part_answer += temp2;
			}*/

			int right;
			// mid2 �߽����� ������
			if (mid2 == i) right = 0;
			else right = ((accu[i].point - accu[mid2].point) - (mid * (accu[i].counts - accu[mid2].counts))) * truck;
			part_answer += right;
			/*
			for (int k = mid2 + 1; k <= i; k++) {
				int temp2 = ((mid - arr[k].point) * arr[k].counts * truck);
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

bool compare(POINT_COUNT a, POINT_COUNT b) {
	// point�� �� ���� ������ �����ϱ�!
	return a.point < b.point;
}