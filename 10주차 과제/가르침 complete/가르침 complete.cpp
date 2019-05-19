// a n t i c �� 5���ڴ� �ʼ��� �ʿ��ϴ�.
// r �� �߰��� ��� anta rc tica�� anta car tica�� ���� �� �ִ�.
// �׷��� anta hello tica�� ���� �� ����.

// ���� ���� K�� 5���� �۴ٸ�, ���� �� �ִ� �ܾ��� ������ ����.
// ���� K�� ��� ���ĺ��� �����Ѵٸ�, ��� ���� �� �ִ�. (K == 26)

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

//#define DEBUG

// �Է¹��� �ܾ �����ϴ� vector
vector<string> words;

// ��� ���ĺ��� ǥ���ϴ� �迭
// a���� z������ �����̸� a�� �ƽ�Ű�ڵ�� 97�̹Ƿ�
// a�� index�� 97-97 = 0�̰�, z�� �ε����� 122-97 = 25�̴�.
// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
int alphabet[26] = { 0, };

// �ܾ ���� �ϴ� ����Լ�
// �ܾ �н��ϴ� ���, �н����� �ʴ� ���� ����
// Ż�� ������ ��� �ܾ K���� ���
void learn(int learned, int alphabet_start);

// ����Լ������� ���� �� �ְ� N, K, answer�� ���������� ����
int N, K;
int answer = 0;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	// k�� 5���� ���� ��� ���� �� �ִ� �ܾ�� ����
	if (K < 5) {
		cout << 0;
		return 0;
	}

	// k�� 26�� ��� ��� �ܾ ���� �� ����
	if (K == 26) {
		cout << N;
		return 0;
	}

	// k�� 5�� �ƴϰ� 26�� �ƴ� ���
	// �ܾ �Է¹޾ƺ���.
	string word;
	for (int i = 0; i < N; i++) {
		cin >> word;

		// �ܾ� �¿쿡 �ִ� anta�� tica�� ���� ����.
		for (int j = 4; j < word.size() - 4; j++) {
			word[j - 4] = word[j];
		}
		word.resize(word.size() - 8);
#ifdef DEBUG
		cout << word << endl;
#endif
		words.push_back(word);
	}

#ifdef DEBUG
	for (int i = 0; i < words.size(); i++)
		cout << words[i] << endl;
#endif


	// ����, a, n, t, i, c�� �ݵ�� ����� �Ѵ�. (K < 5�϶��� �̹� �տ��� �����)
	// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
	// �� 5���� ���� 1�� ������Ŵ (0�� �ƴ� �� ����ٴ� �ǹ�)
	alphabet[0]++;
	alphabet[2]++;
	alphabet[8]++;
	alphabet[13]++;
	alphabet[19]++;

	// K�� ������ 5�� ����. (a, n, t, i, c�� �ʼ��̹Ƿ�)
	K = K - 5;

	// ����Լ��� ���ؼ� �ܾ �н��ϰ� �Ѵ�.
	learn(0, 0); // ó���� ���� �ܾ�� 0��, a(= 97-97 = 0)���� ����
	cout << answer;
	return 0;
}

void learn(int learned, int alphabet_start) {
	
#ifdef DEBUG
	cout << "����� �ϴ� ���ĺ��� : " << (char)(alphabet_start+97) << endl;
#endif

	// ���� ����� �ϴ� ���ĺ��� �� ä�� ���
	if (learned == K) {
		int part_answer = 0;

		// ��� �ܾ ���� ��� �� �ִ��� ������ �˻���
		for (int i = 0; i < N; i++) {
			// �� �ܾ ����� ���� ���ĺ��� ������ ��� �� ����
			// a�� ��� �ƽ�Ű�ڵ�� 97
			int sw = 0;
			for (int j = 0; j < words[i].length(); j++) {
				if (alphabet[(int)words[i][j] - 97] == 0) {
					sw = 1;
					break;
				}
			}
			// ���� ��� �� �ִ� �ܾ ������ part_answer����
			if (sw == 0) {
#ifdef DEBUG
				cout << "part_answer����!" << endl;
#endif
				part_answer++;
			}
		}

		// ������ ����� ���Ͽ� �� ũ�� ��ü
		if (answer < part_answer) {
#ifdef DEBUG
			cout << part_answer << "�� ���� ��ü" << endl;
#endif
			answer = part_answer;
		}

		// ���ȣ�� ����
		return;
	}
	else {
		// ���� ����� �ϴ� ���ĺ��� �� ä���� ���� ��� -> ���ȣ��
		for (int i = alphabet_start; i < 26; i++) {
			if (alphabet[i] == 0) {
				alphabet[i]++; // ���ĺ��� ���
				learn(learned + 1, i); // ���ȣ��
				// �� ���ĺ��� �ٽ� ����� ���� ���·� ������,
				// �� ���¿��� �ٸ� ���ĺ��� ���� ���ȣ���ϰ�...
				alphabet[i]--; 
			}
		}
	}
}