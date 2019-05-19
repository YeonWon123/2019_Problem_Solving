#include <string>
#include <stack>
#include <iostream>
using namespace std;

// ������ �̿��� ¦�� ���� �ʴ� ��ȣ ������ �ذ��ϴ� �˰���
bool wellMatched(const string& formula) {
	// ���� ��ȣ ���ڵ�� �ݴ� ��ȣ ���ڵ�
	const string opening("({["), closing(")}]");
	// �̹� ���� ��ȣ���� ������� ��� ����
	stack<char> openStack;
	for (int i = 0; i < formula.size(); ++i)
		// ���� ��ȣ���� �ݴ� ��ȣ���� Ȱ���Ѵ�.
		if (opening.find(formula[i]) != -1)
			// ���� ��ȣ��� ������ ���ÿ� ����ִ´�.
			openStack.push(formula[i]);
		else {
			// �� ���� ��� ���� �� ���� ���ڿ� ���纸��.
			// ������ ��� �ִ� ��쿡�� ����
			if (openStack.empty()) return false;
			// ���� ¦�� ���� �ʾƵ� ����
			if(opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			// ¦�� ���� ��ȣ�� ���ÿ��� ����.
			openStack.pop();
		}
	// ������ ���� ��ȣ�� ����� ����
	return openStack.empty();
}

int main()
{
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		string formula;
		cin >> formula;
		if (wellMatched(formula)) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}