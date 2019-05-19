// a n t i c 이 5글자는 필수로 필요하다.
// r 이 추가될 경우 anta rc tica와 anta car tica를 읽을 수 있다.
// 그러나 anta hello tica는 읽을 수 없다.

// 따라서 만약 K가 5보다 작다면, 읽을 수 있는 단어의 개수가 없다.
// 만약 K가 모든 알파벳을 포함한다면, 모두 읽을 수 있다. (K == 26)

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

//#define DEBUG

vector<string> words;

// a부터 z까지의 순서이며 a는 아스키코드로 97이므로
// a의 index는 97-97 = 0이고, z의 인덱스는 122-97 = 25이다.
// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
char alphabet[26];
int scount = 0;
void learn(int learned, string learned_alpha, string alphabet_capture, string alphabet_part[], int alphabet_count[]);

int N, K; // 재귀함수에서도 통할 수 있게 N, K를 전역변수로 선언
int answer = 0;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int answer_first = 0;
	cin >> N >> K;

	// k가 5보다 작을 경우 읽을 수 있는 단어는 없음
	if (K < 5) {
		cout << 0;
		return 0;
	}

	// k가 26일 경우 모든 단어를 읽을 수 있음
	if (K == 26) {
		cout << N;
		return 0;
	}

	// k가 5도 아니고 26도 아닐 경우
	// 단어를 입력받아보자.
	string word;
	string alphabet_capture;
	string alphabet_part[50];
	int alphabet_count[50] = { 0, };
	for (int i = 0; i < N; i++) {
		cin >> word;

		// 단어 좌우에 있는 anta와 tica를 없애 보자.
		// 이때 antatica처럼 anta와 tica로만 이루어진 단어가 있을 수 있다.
		// 이 경우 answer를 증가시킨다.(words.size()가 8이면, a를 하나 추가하면 된다.)
		if (word.size() == 8) {
			answer_first++;
		}
		else {
			// 만약 a, n, t, i, c로만 이루어진 언어라면 answer++ 이후 continue
			// 먼저 a, n, t, i, c로만 이루어져 있는지 확인
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
				// a, n, t, i, c를 제외
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

	// 모으기
	// a, n, t, i, c를 제외하고, alphabet[] = 0인 것도 제외하자.
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
	// 재귀함수를 통해서 단어를 학습하게 함
	// 재귀함수는 단어를 학습하는 경우, 학습하지 않는 경우로 나눔
	// 탈출 조건은 배운 단어가 K개인 경우
	string learned_alphabet;
	learn(0, learned_alphabet, alphabet_capture, alphabet_part, alphabet_count);

	cout << answer_first + answer;
	return 0;
}

void learn(int learned, string learned_alpha, string alphabet_capture, string alphabet_part[], int alphabet_count[]) {

	// 만약 배워야 하는 알파벳을 다 채운 경우
	if (learned == K) {
		int temp;
		int part_answer = 0;

		// 모든 단어에 대해 배울 수 있는지 유무를 검사함
		for (int i = 0; i < N; i++) {
			temp = 0;
			// j개의 알파벳 검사
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

	// 만약 배워야 하는 알파벳을 다 채우지 못한 경우 - 재귀 호출
	for (int i = 0; i < alphabet_capture.size(); i++) {
		learn(learned + 1, learned_alpha, alphabet_capture, alphabet_part, alphabet_count);
	}
}