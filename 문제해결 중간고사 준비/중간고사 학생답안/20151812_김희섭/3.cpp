#include <iostream>
using namespace std;

int price[101];
int num[101];
int dp[10001];//인덱스까지가 지폐
int temp_dp[10001];//임시 저장 공간

int main()
{
	int T;//지폐금액
	int k;//동전의 가지수
	cin >> T;
	cin >> k;
	int i,j,l;
	int temp_price;
	for (i = 0; i < k; i++)
	{
		cin >> price[i];
		cin >> num[i];
	}

	temp_dp[0] = 1;
	dp[0] = 1;

	for (i = 0; i < k; i++)//동전의 종류마다 고려
	{

		//배열을 복사
		for (j = 0; j <= T; j++)
		{
			temp_dp[j] = dp[j];
		}


		for (j = num[i]; j >= 1; j--)
		{
			temp_price = price[i] * j;
			for (l = T; l >= temp_price; l--)
			{
				dp[l] += temp_dp[l - temp_price];
			}
		}
	}

	cout << dp[T] << endl;
	
	return 0;
}