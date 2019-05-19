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

// 입력받은 단어를 보관하는 vector
vector<string> words;

// 배운 알파벳을 표시하는 배열
// a부터 z까지의 순서이며 a는 아스키코드로 97이므로
// a의 index는 97-97 = 0이고, z의 인덱스는 122-97 = 25이다.
// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
int alphabet[26] = { 0, };

// 단어를 배우게 하는 재귀함수
// 단어를 학습하는 경우, 학습하지 않는 경우로 나눔
// 탈출 조건은 배운 단어가 K개인 경우
void learn(int learned, int alphabet_start);

// 재귀함수에서도 통할 수 있게 N, K, answer를 전역변수로 선언
int N, K;
int answer = 0;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

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
	for (int i = 0; i < N; i++) {
		cin >> word;

		// 단어 좌우에 있는 anta와 tica를 없애 보자.
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


	// 먼저, a, n, t, i, c는 반드시 배워야 한다. (K < 5일때는 이미 앞에서 고려함)
	// a : 97-97 = 0, c : 99-97 = 2, i : 105-97 = 8,  n : 110 - 97 = 13, t : 116-97 = 19
	// 이 5개는 먼저 1씩 증가시킴 (0이 아닌 건 배웠다는 의미)
	alphabet[0]++;
	alphabet[2]++;
	alphabet[8]++;
	alphabet[13]++;
	alphabet[19]++;

	// K의 값에서 5를 뺀다. (a, n, t, i, c는 필수이므로)
	K = K - 5;

	// 재귀함수를 통해서 단어를 학습하게 한다.
	learn(0, 0); // 처음에 배우는 단어는 0개, a(= 97-97 = 0)부터 시작
	cout << answer;
	return 0;
}

void learn(int learned, int alphabet_start) {
	
#ifdef DEBUG
	cout << "배워야 하는 알파벳은 : " << (char)(alphabet_start+97) << endl;
#endif

	// 만약 배워야 하는 알파벳을 다 채운 경우
	if (learned == K) {
		int part_answer = 0;

		// 모든 단어에 대해 배울 수 있는지 유무를 검사함
		for (int i = 0; i < N; i++) {
			// 각 단어에 배우지 않은 알파벳이 있으면 배울 수 없음
			// a의 경우 아스키코드로 97
			int sw = 0;
			for (int j = 0; j < words[i].length(); j++) {
				if (alphabet[(int)words[i][j] - 97] == 0) {
					sw = 1;
					break;
				}
			}
			// 만약 배울 수 있는 단어가 있으면 part_answer증가
			if (sw == 0) {
#ifdef DEBUG
				cout << "part_answer증가!" << endl;
#endif
				part_answer++;
			}
		}

		// 기존의 정답과 비교하여 더 크면 교체
		if (answer < part_answer) {
#ifdef DEBUG
			cout << part_answer << "로 정답 교체" << endl;
#endif
			answer = part_answer;
		}

		// 재귀호출 종료
		return;
	}
	else {
		// 만약 배워야 하는 알파벳을 다 채우지 못한 경우 -> 재귀호출
		for (int i = alphabet_start; i < 26; i++) {
			if (alphabet[i] == 0) {
				alphabet[i]++; // 알파벳을 배움
				learn(learned + 1, i); // 재귀호출
				// 그 알파벳을 다시 배우지 않은 상태로 돌리고,
				// 그 상태에서 다른 알파벳을 배우고 재귀호출하게...
				alphabet[i]--; 
			}
		}
	}
}