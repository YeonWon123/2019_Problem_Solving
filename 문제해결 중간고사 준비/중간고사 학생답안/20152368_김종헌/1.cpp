#include <cstdio>
#include <vector>
using namespace std;
int main() {
	int n, onum[3] = { 0,2,0 }, mnum = 1,sum=2,t=3; scanf("%d", &n);
	while (sum + 1 < n) {
		int tmp = onum[0] + onum[1] + onum[2];
		onum[0] = onum[2] = tmp; onum[1]++;
		mnum = (mnum * 2 + 1);
		sum = (onum[0] + onum[1] + onum[2] + mnum);
	}
	if (sum+1 == n) { printf("m"); }
	else {
		sum++;
		int a = 2;
		vector<int> ans(1, 2);
		while (sum-a > n) {
			int l = ans.size();
			a += t;
			ans.push_back(t++);
			for (int i = 0; i < l; i++) {
				ans.push_back(ans[i]);
				a += ans[i];
				if (sum-a <= n) { break; }
			}
		}
		for (int i = 0, l = ans.size(); i < l; i++) {
			sum -= (ans[i]+1);
			if (sum <= n) { break; }
		}
		printf("%c", (sum == n ? 'm' : 'o'));
	}
}