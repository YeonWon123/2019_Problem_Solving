#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// #define DEBUG

// �� ������ ������ ���ڸ� ��� �迭
int *arr;

// �Է¿����� �ִ񰪰� �Է¿����� ���� �����ϴ� ��
// �Է¿��Ҵ� 100 ������ �ڿ����̹Ƿ�
// ù ���Ҹ� �Է¹��� �� �񱳿����� �����ϵ��� ����
int max_input = -1;
int sum_input = 0;

// ������ ���� �����ϴ� ����
vector<int> bead_count;

// �׷��� �� �� �ִ��� i�� �Ѵ��� �׽�Ʈ�Ͽ� 
// ������ false�� ��ȯ, �ִ��� i��� true�� ��ȯ
// ��, ���ʺ��� �������� x ���ϰ� �ǵ��� �������,
// M ������ �׷����� ���� �� �ִ��� �׽�Ʈ!
// N�� ������ ����, M�� �׷��� ����
bool greedy(int max_sum, int N, int M);

// �ִ��� �ִ� �κ��� ��ġ�� ���� ������
int max_locate;

int main(void)
{
	int N, M; // N : ������ ����, M : �׷��� ��
	cin >> N >> M;

	arr = new int[N];

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (max_input < arr[i]) max_input = arr[i];
		sum_input += arr[i];
	}
	
	int max_sum;
	// �׷��� �� �� �ִ��� i�� �Ѵ��� �׽�Ʈ�Ͽ� ������ ���� ����
	for (max_sum = max_input; max_sum <= sum_input; max_sum++)
	{
		if(greedy(max_sum, N, M)) break;
#ifdef DEBUG
		cout << "max_sum: " << max_sum << "�� ����!" << endl;
#endif
	}

	// ��� ���
	cout << max_sum << "\n";
	if (bead_count.size() == M) {
		for (int i = 0; i < bead_count.size(); i++)
			cout << bead_count[i] << " ";
	}
	else
	{
		deque<int> new_bead_count;
		for (int i = 0; i < bead_count.size(); i++)
			new_bead_count.push_back(bead_count[i]);

		deque<int>::iterator p = new_bead_count.begin();
		int not_move_max_locate = 0;
		// �ִ��� �ִ� �κ��� ������, ������ �κ��� divide�Ѵ�.
		for (int i = 0; (new_bead_count.size() < M); i++)
		{
			p = new_bead_count.begin();
#ifdef DEBUG
			cout << "\n";
			cout << "i�� �� : " << i << endl;
			// �ִ��� �ִ� �κ��� ������ �ʴ´�.
			cout << "max_locate : " << max_locate << endl;
#endif
			if (i == max_locate && not_move_max_locate == 0)
			{
				not_move_max_locate = 1;
				continue;
			}
			
			// ������ �κ��� ������.
			if (new_bead_count[i] != 1)
			{
				p = p + i;
				int temp;
				temp = new_bead_count[i];
				new_bead_count.erase(p);
				p = new_bead_count.begin() + i;
				new_bead_count.insert(p, temp - 1);
				p = new_bead_count.begin() + i + 1;
				new_bead_count.insert(p, 1);
				max_locate++;
				i--;
			}
		}

		// ���ڶ�� �������� ä�� ����Ѵ�.
		for (int i = 0; i < new_bead_count.size(); i++)
			cout << new_bead_count[i] << " ";
	}

	return 0;
}

bool greedy(int max_sum, int N, int M)
{
	int *part_sum;
	part_sum = new int[M];
	for (int i = 0; i < M; i++) {
		part_sum[i] = 0;
	}

	int i(0), temp(0), bead_count_sum(0), sw(0);
	while(i < M) {
		if (part_sum[i] <= max_sum)
		{	
			part_sum[i] += arr[temp];
#ifdef DEBUG
			cout << "part_sum[" << i << "]: " << part_sum[i] << endl;
#endif

			// �ִ��� �ִ� �κ��� ��ġ�� ���� ������
			if (part_sum[i] == max_sum)
			{
				if (sw == 0)
				{
					sw = 1;
					max_locate = bead_count.size();
				}
				else // �ִ��� �ִ� �κ��� ���� ���� ���
					 // �׷쿡 ���Ե� ������ �� ���� ���� ��ġ�� ����
				{
					bead_count_sum = 0;
					for (int j = 0; j < bead_count.size(); j++) {
						bead_count_sum += bead_count[j];
					}
					if (bead_count[max_locate] > temp - bead_count_sum)
						max_locate = bead_count.size();
				}
#ifdef DEBUG
				cout << "max_locate : " << max_locate << endl;
#endif
			}

			temp++;
			if (temp == N) {
				if (part_sum[i] > max_sum) {
					temp = temp - 1;
				goto THISWAY;
				}

				bead_count_sum = 0;
				for (int j = 0; j < bead_count.size(); j++) {
					bead_count_sum += bead_count[j];
				}
#ifdef DEBUG
				cout << "�׷� ���� ����: " << temp - bead_count_sum << endl;
#endif
				bead_count.push_back(temp - bead_count_sum);
				return true;
			}
		}
		else
		{			
			temp = temp - 1;
		THISWAY:
			bead_count_sum = 0;
			for (int j = 0; j < bead_count.size(); j++) {
				bead_count_sum += bead_count[j];
			}

#ifdef DEBUG
			cout << "�׷� ���� ����: " << temp - bead_count_sum << endl;
#endif
			bead_count.push_back(temp - bead_count_sum);
			i++;
		}
	}

	bead_count.clear();
	return false;
}