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

vector<string> words;

// a���� z������ �����̸� a�� �ƽ�Ű�ڵ�� 97�̹Ƿ�
// a�� index�� 97-97 = 0�̰�, z�� �ε����� 122-97 = 25�̴�.
// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
char alphabet[26];
int scount = 0;
void learn(int learned, string learned_alpha, string alphabet_capture, string alphabet_part[], int alphabet_count[]);

int N, K; // ����Լ������� ���� �� �ְ� N, K�� ���������� ����
int answer = 0;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int answer_first = 0;
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
	string alphabet_capture;
	string alphabet_part[50];
	int alphabet_count[50] = { 0, };
	for (int i = 0; i < N; i++) {
		cin >> word;

		// �ܾ� �¿쿡 �ִ� anta�� tica�� ���� ����.
		// �̶� antaticaó�� anta�� tica�θ� �̷���� �ܾ ���� �� �ִ�.
		// �� ��� answer�� ������Ų��.(words.size()�� 8�̸�, a�� �ϳ� �߰��ϸ� �ȴ�.)
		if (word.size() == 8) {
			answer_first++;
		}
		else {
			// ���� a, n, t, i, c�θ� �̷���� ����� answer++ ���� continue
			// ���� a, n, t, i, c�θ� �̷���� �ִ��� Ȯ��
			int counts = 0;
			int j;
			for (j = 0; j < word.size(); j++) {
				if (word[j] == 'a' || word[j] == 'n' || word[j] == 't' || word[j] == 'i' || word[j] == 'c') {
					counts++;
				}
			}
			if (word.size() == counts) {
				answer_first++;
				continue;
			}

			for (j = 4; j < word.size() - 4; j++) {
				word[j - 4] = word[j];
				int temp = (int)word[j] - 97;
				alphabet[temp]++;
				// a, n, t, i, c�� ����
				// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
				if (temp != 0 && temp != 2 && temp != 8 && temp != 13 && temp != 19) {
					int sw = 0;
					for (int m = 0; m < alphabet_part[i].size(); m++) {
						if (alphabet_part[i][m] == word[j]) {
							sw = 1;
							break;
						}
					}
					if (sw == 0) {
						alphabet_part[i].push_back(word[j]);
						alphabet_count[i]++;
					}
				}
			}
			word.resize(j - 4);
			words.push_back(word);
		}
	}

	// ������
	// a, n, t, i, c�� �����ϰ�, alphabet[] = 0�� �͵� ��������.
	// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
	for (int i = 0; i < 24; i++) {
		if (i == 0 || i == 2 || i == 8 || i == 13 || i == 19)
			continue;

		if (alphabet[i] == 0)
			continue;

		alphabet_capture.push_back((char)(i + 97));
	}

#ifdef DEBUG

	for (int i = 0; i < words.size(); i++)
		cout << words[i] << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < alphabet_part[i].size(); j++)
			cout << alphabet_part[i][j] << " ";
		cout << endl << alphabet_count[i] << endl;
	}

	for (int i = 0; i < alphabet_capture.size(); i++)
		cout << alphabet_capture[i] << endl;

#endif

	K = K - 5;
	// ����Լ��� ���ؼ� �ܾ �н��ϰ� ��
	// ����Լ��� �ܾ �н��ϴ� ���, �н����� �ʴ� ���� ����
	// Ż�� ������ ��� �ܾ K���� ���
	string learned_alphabet;
	learn(0, learned_alphabet, alphabet_capture, alphabet_part, alphabet_count);

	cout << answer_first + answer;
	return 0;
}

void learn(int learned, string learned_alpha, string alphabet_capture, string alphabet_part[], int alphabet_count[]) {

	// ���� ����� �ϴ� ���ĺ��� �� ä�� ���
	if (learned == K) {
		int temp;
		int part_answer = 0;

		// ��� �ܾ ���� ��� �� �ִ��� ������ �˻���
		for (int i = 0; i < N; i++) {
			temp = 0;
			// j���� ���ĺ� �˻�
			char ch1[30], ch2[2];
			strcpy(ch1, alphabet_part[i].c_str());
			for (int j = 0; j < K; j++) {
				ch2[0] = learned_alpha[j];
				ch2[1] = '\0';
				if (strstr(ch1, ch2) != 0) {
					//if (alphabet_part[i].find(learned_alpha[j]) != string::npos) {
					temp++;
				}
			}

			if (temp == alphabet_part[i].size())
				part_answer++;
		}

		if (answer < part_answer)
			answer = part_answer;

		return;
	}

	// ���� ����� �ϴ� ���ĺ��� �� ä���� ���� ��� - ��� ȣ��
	for (int i = 0; i < alphabet_capture.size(); i++) {
		learn(learned + 1, learned_alpha, alphabet_capture, alphabet_part, alphabet_count);
	}
}