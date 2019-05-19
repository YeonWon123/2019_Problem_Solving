#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
using namespace std;

//#define DEBUG

typedef struct POINT {
	int x;
	int y;

	// operator overloading
	bool operator < (const POINT &a) const {
		return ((x < a.x) || ((x == a.x) && (y < a.y)));
	}

} point;

set<point> input;
stack<point> convex_hull;

// 삼각형의 넓이를 구하는 함수
double SignArea(point a, point b, point c) {
	double area = 0.5 * (a.x * b.y - a.y * b.x + b.x * c.y - c.x * b.y + c.x * a.y - a.x * c.y);
#ifdef DEBUG
	// printf("넓이 : %f\n", area);
#endif
	return area;
}

// 점과 점 사이의 거리를 구하는 함수
double dim(point a, point b) {
	double dimension = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
#ifdef DEBUG
	// printf("점 사이 거리 : %lf\n", dimension);
#endif
	return dimension;
}

// 같은 선분 위에 있지 않게 정렬해주는 함수
// 같은 선분 위에 있으면, p_0으로부터의 길이가 작은 것을 앞으로 오게 하고, 큰 것을 뒤로 가게 한다. (세번째 줄)
// 그렇지 않으면, 시계 반대 방향으로 점들이 위치할 수 있게 해 준다. (두번째 줄)
point p_0;
bool sort_compare(point a, point b) {
	int area = SignArea(p_0, a, b);
	if (area) return area > 0;
	return dim(p_0, a) < dim(p_0, b);
}

int main(void)
{
	// cin과 cout의 속도를 빠르게
	ios_base::sync_with_stdio(false);	cin.tie(NULL);	cout.tie(NULL);

	// 소수점 설정
	cout << fixed;
	cout.precision(9);

	int C;
	cin >> C;

	point temp;
	for (int i = 0; i < C; i++) {
		cin >> temp.x >> temp.y;
		input.insert(temp);
	}

	set<point>::iterator it;

#ifdef DEBUG
	// 입력받음 + 정렬된 좌표들을 출력해주는 부분
	// 1. 먼저 같은 위치에 있는 좌표를 걸러주었음
	cout << endl << "입력받아 정렬된 좌표들" << endl;
	for (it = input.begin(); it != input.end(); it++) 
		cout << (*it).x << " " << (*it).y << endl;
	
#endif
	// 2. 만약 P_0점 (x의 좌표가 제일 작은 점, 같을 경우 y의 좌표가 제일 작은 점)을 기준으로
	// 세 점 이상이 같은 선분에 위치할 경우,
	// P_0점에서 가장 멀리 있는 점만 살려야 한다.
	// 그 정렬을 수행해 보자.

	vector<point> unique_input;
	it = input.begin();
	p_0 = *it;
	for (int i = 0; i < input.size(); i++) {
		unique_input.push_back(*it);
		it++;
	}
	
	sort(unique_input.begin() + 1, unique_input.end(), sort_compare);

#ifdef DEBUG
	cout << endl << endl << "재정렬된 좌표들" << endl;
	for (int i = 0; i < unique_input.size(); i++)
		cout << unique_input[i].x << " " << unique_input[i].y << endl;
#endif
	   	   	
	// convex hull O(nlogn)
	// x좌표가 가장 작은 곳부터 탐색 시작
	// 먼저 0번째 값과 첫번째 값은 stack에 저장한다.

	// 예외 처리 - 만약 점이 1개만 있다고 판정나면 프로그램 종료
	// 즉 같은 점이 계속 들어올 경우
	if (input.size() == 1) {
		cout << 0;
		return 0;
	}
	
	convex_hull.push(unique_input[0]);
	convex_hull.push(unique_input[1]);

	int next = 2;
	// next가 2가 될 때부터, 끝까지 갈 때까지 탐색을 시작한다.
	while(next < unique_input.size()) {
#ifdef DEBUG
		printf("next : %d\n", next);
#endif
		// 스택에 들어 있는 개수가 2보다 같거나 크면, 위에서 두개를 뺀다.
		// 그리고 그 뒤의 점과 함께 삼각형을 구성한 뒤 넓이를 계산해서,
		// 양수이면 뽑았던 값을 다시 집어넣고
		// 음수이면 집어넣지 않고 다음거를 탐색한다.
		while (convex_hull.size() >= 2) {
			point first, second;
			second = convex_hull.top();
			convex_hull.pop();
			first = convex_hull.top();

			if (SignArea(first, second, unique_input[next]) > 0) {
				convex_hull.push(second);
				break;
			}
		}

		// 다음 값을 집어넣자
		convex_hull.push(unique_input[next]);
		next++;
	}
/*
#ifdef DEBUG
	cout << endl << "Convex_hull 좌표 개수 : " << convex_hull.size() << endl;
	// Convex_hull의 점들을 출력해주는 부분
	cout << endl << "Convex_hull의 점들" << endl;
	while (!convex_hull.empty()) {
		temp = convex_hull.top();
		cout << temp.x << " " << temp.y << endl;
		convex_hull.pop();
	}

	return 0;
#endif
*/
	// Diameter 구하기(O(n ^ 2) 또는 Rotating Calipers(O(n)))
	double answer = 0;
	int j = 1;
	int h = convex_hull.size();
#ifdef DEBUG
	cout << "h : " << h << endl;
#endif
	point *arr;
	arr = new point[h];

	for (int i = h-1; i >= 0; i--) {
		temp = convex_hull.top();
		arr[i].y = temp.y;
		arr[i].x = temp.x;
		convex_hull.pop();
	}
		
#ifdef DEBUG
	cout << endl << "arr 출력" << endl;
	for (int i = 0; i < h; i++) {
		cout << arr[i].x << " " << arr[i].y << endl;
	}
#endif

	for (int i = 0; i < h; i++) {
		// 점1 ~ 점2 사이 선분과 점 j의 거리 < 점1 ~ 점2 사이 선분과 점 j+1의 거리
		while (SignArea(arr[i], arr[(i+1)%h], arr[j%h]) < SignArea(arr[i], arr[(i+1)%h], arr[(j+1)%h])) 
			j = (j + 1) % h;
		
		if (answer < dim(arr[i], arr[j])) answer = dim(arr[i], arr[j]);
	}
#ifdef DEBUG
	cout << "최종 답안 : ";
#endif
	cout << answer;
	return 0;
}