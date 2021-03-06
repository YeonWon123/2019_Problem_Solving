#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// #define DEBUG

// 각 구슬에 적혀진 숫자를 담는 배열
int *arr;

// 입력원소중 최댓값과 입력원소의 합을 저장하는 수
// 입력원소는 100 이하의 자연수이므로
// 첫 원소를 입력받을 때 비교연산이 가능하도록 설정
int max_input = -1;
int sum_input = 0;

// 구슬의 수를 저장하는 벡터
vector<int> bead_count;

// 그룹의 합 중 최댓값이 i를 넘는지 테스트하여 
// 넘으면 false를 반환, 최댓값이 i라면 true를 반환
// 즉, 왼쪽부터 구간합이 x 이하가 되도록 나누어가면,
// M 이하의 그룹으로 나눌 수 있는지 테스트!
// N은 구슬의 갯수, M은 그룹의 갯수
bool greedy(int max_sum, int N, int M);

// 최댓값이 있는 부분의 위치를 따로 가져옴
int max_locate;

int main(void)
{
	int N, M; // N : 구슬의 개수, M : 그룹의 수
	cin >> N >> M;

	arr = new int[N];

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (max_input < arr[i]) max_input = arr[i];
		sum_input += arr[i];
	}
	
	int max_sum;
	// 그룹의 합 중 최댓값이 i를 넘는지 테스트하여 넘으면 루프 종료
	for (max_sum = max_input; max_sum <= sum_input; max_sum++)
	{
		if(greedy(max_sum, N, M)) break;
#ifdef DEBUG
		cout << "max_sum: " << max_sum << "은 실패!" << endl;
#endif
	}

	// 답안 출력
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
		// 최댓값이 있는 부분을 제외한, 나머지 부분을 divide한다.
		for (int i = 0; (new_bead_count.size() < M); i++)
		{
			p = new_bead_count.begin();
#ifdef DEBUG
			cout << "\n";
			cout << "i의 값 : " << i << endl;
			// 최댓값이 있는 부분은 나누지 않는다.
			cout << "max_locate : " << max_locate << endl;
#endif
			if (i == max_locate && not_move_max_locate == 0)
			{
				not_move_max_locate = 1;
				continue;
			}
			
			// 나머지 부분을 나눈다.
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

		// 모자라는 구간수를 채워 출력한다.
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

			// 최댓값이 있는 부분의 위치를 따로 가져옴
			if (part_sum[i] == max_sum)
			{
				if (sw == 0)
				{
					sw = 1;
					max_locate = bead_count.size();
				}
				else // 최댓값이 있는 부분이 여러 곳일 경우
					 // 그룹에 포함된 갯수가 더 작은 곳을 위치로 삼음
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
				cout << "그룹 구슬 개수: " << temp - bead_count_sum << endl;
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
			cout << "그룹 구슬 개수: " << temp - bead_count_sum << endl;
#endif
			bead_count.push_back(temp - bead_count_sum);
			i++;
		}
	}

	bead_count.clear();
	return false;
}