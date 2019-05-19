#include <list>
#include <iostream>
using namespace std;

// ���� ����Ʈ�� �̿��� ����Ǫ�� ������ ����
void josephus(int n, int k) {
	// ����Ʈ�� �غ��Ѵ�.
	list<int> survivors;
	for (int i = 1; i <= n; i++) survivors.push_back(i);
	// �̹��� ���� ����� ��Ÿ���� ������
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		// ù ��° ����� �ڻ��Ѵ�. erase()�� ���� ������ ���� ���Ҹ� ��ȯ�Ѵ�.
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();
		--n;
		// k-1�� ���� ������� �ű��.
		for (int i = 0; i < k - 1; ++i) {
			++kill;
			if (kill == survivors.end()) kill = survivors.begin();
		}
	}

	cout << survivors.front() << " " << survivors.back() << endl;
}

int main()
{
	int C, N, K;
	cin >> C;

	for (int i = 0; i < C; i++)
	{
		cin >> N >> K;
		josephus(N, K);
	}

	return 0;
}