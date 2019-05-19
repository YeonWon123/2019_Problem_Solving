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

// �ﰢ���� ���̸� ���ϴ� �Լ�
double SignArea(point a, point b, point c) {
	double area = 0.5 * (a.x * b.y - a.y * b.x + b.x * c.y - c.x * b.y + c.x * a.y - a.x * c.y);
#ifdef DEBUG
	// printf("���� : %f\n", area);
#endif
	return area;
}

// ���� �� ������ �Ÿ��� ���ϴ� �Լ�
double dim(point a, point b) {
	double dimension = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
#ifdef DEBUG
	// printf("�� ���� �Ÿ� : %lf\n", dimension);
#endif
	return dimension;
}

// ���� ���� ���� ���� �ʰ� �������ִ� �Լ�
// ���� ���� ���� ������, p_0���κ����� ���̰� ���� ���� ������ ���� �ϰ�, ū ���� �ڷ� ���� �Ѵ�. (����° ��)
// �׷��� ������, �ð� �ݴ� �������� ������ ��ġ�� �� �ְ� �� �ش�. (�ι�° ��)
point p_0;
bool sort_compare(point a, point b) {
	int area = SignArea(p_0, a, b);
	if (area) return area > 0;
	return dim(p_0, a) < dim(p_0, b);
}

int main(void)
{
	// cin�� cout�� �ӵ��� ������
	ios_base::sync_with_stdio(false);	cin.tie(NULL);	cout.tie(NULL);

	// �Ҽ��� ����
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
	// �Է¹��� + ���ĵ� ��ǥ���� ������ִ� �κ�
	// 1. ���� ���� ��ġ�� �ִ� ��ǥ�� �ɷ��־���
	cout << endl << "�Է¹޾� ���ĵ� ��ǥ��" << endl;
	for (it = input.begin(); it != input.end(); it++) 
		cout << (*it).x << " " << (*it).y << endl;
	
#endif
	// 2. ���� P_0�� (x�� ��ǥ�� ���� ���� ��, ���� ��� y�� ��ǥ�� ���� ���� ��)�� ��������
	// �� �� �̻��� ���� ���п� ��ġ�� ���,
	// P_0������ ���� �ָ� �ִ� ���� ����� �Ѵ�.
	// �� ������ ������ ����.

	vector<point> unique_input;
	it = input.begin();
	p_0 = *it;
	for (int i = 0; i < input.size(); i++) {
		unique_input.push_back(*it);
		it++;
	}
	
	sort(unique_input.begin() + 1, unique_input.end(), sort_compare);

#ifdef DEBUG
	cout << endl << endl << "�����ĵ� ��ǥ��" << endl;
	for (int i = 0; i < unique_input.size(); i++)
		cout << unique_input[i].x << " " << unique_input[i].y << endl;
#endif
	   	   	
	// convex hull O(nlogn)
	// x��ǥ�� ���� ���� ������ Ž�� ����
	// ���� 0��° ���� ù��° ���� stack�� �����Ѵ�.

	// ���� ó�� - ���� ���� 1���� �ִٰ� �������� ���α׷� ����
	// �� ���� ���� ��� ���� ���
	if (input.size() == 1) {
		cout << 0;
		return 0;
	}
	
	convex_hull.push(unique_input[0]);
	convex_hull.push(unique_input[1]);

	int next = 2;
	// next�� 2�� �� ������, ������ �� ������ Ž���� �����Ѵ�.
	while(next < unique_input.size()) {
#ifdef DEBUG
		printf("next : %d\n", next);
#endif
		// ���ÿ� ��� �ִ� ������ 2���� ���ų� ũ��, ������ �ΰ��� ����.
		// �׸��� �� ���� ���� �Բ� �ﰢ���� ������ �� ���̸� ����ؼ�,
		// ����̸� �̾Ҵ� ���� �ٽ� ����ְ�
		// �����̸� ������� �ʰ� �����Ÿ� Ž���Ѵ�.
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

		// ���� ���� �������
		convex_hull.push(unique_input[next]);
		next++;
	}
/*
#ifdef DEBUG
	cout << endl << "Convex_hull ��ǥ ���� : " << convex_hull.size() << endl;
	// Convex_hull�� ������ ������ִ� �κ�
	cout << endl << "Convex_hull�� ����" << endl;
	while (!convex_hull.empty()) {
		temp = convex_hull.top();
		cout << temp.x << " " << temp.y << endl;
		convex_hull.pop();
	}

	return 0;
#endif
*/
	// Diameter ���ϱ�(O(n ^ 2) �Ǵ� Rotating Calipers(O(n)))
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
	cout << endl << "arr ���" << endl;
	for (int i = 0; i < h; i++) {
		cout << arr[i].x << " " << arr[i].y << endl;
	}
#endif

	for (int i = 0; i < h; i++) {
		// ��1 ~ ��2 ���� ���а� �� j�� �Ÿ� < ��1 ~ ��2 ���� ���а� �� j+1�� �Ÿ�
		while (SignArea(arr[i], arr[(i+1)%h], arr[j%h]) < SignArea(arr[i], arr[(i+1)%h], arr[(j+1)%h])) 
			j = (j + 1) % h;
		
		if (answer < dim(arr[i], arr[j])) answer = dim(arr[i], arr[j]);
	}
#ifdef DEBUG
	cout << "���� ��� : ";
#endif
	cout << answer;
	return 0;
}