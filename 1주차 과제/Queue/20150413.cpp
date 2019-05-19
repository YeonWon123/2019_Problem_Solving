#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

void leftmove(deque<int> &circlequeue, int select, int &sw);
void rightmove(deque<int> &circlequeue, int select, int &sw);

int main()
{
	deque<int> circlequeue1, circlequeue2;
	int N, M;
	cin >> N >> M;
	int sw, leftmoving, rightmoving;
	int answer = 0;

	for (int i = 1; i <= N; i++)
	{
		circlequeue1.push_back(i);
		circlequeue2.push_back(i);
	}

	for (int i = 1; i <= M; i++)
	{
		int select;
		cin >> select;
		sw = 0;
		leftmoving = 0;
		rightmoving = 0;

		while (1)
		{
			leftmove(circlequeue1, select, sw);
			if (sw == 1) break;
			leftmoving++;
		}

		sw = 0;

		while (1)
		{
			rightmove(circlequeue2, select, sw);
			if (sw == 1) break;
			rightmoving++;
		}

		if (leftmoving < rightmoving)
			circlequeue2 = circlequeue1;
		else
			circlequeue1 = circlequeue2;

		answer = answer + min(leftmoving, rightmoving);
	}

	cout << answer << "\n";
	return 0;
}

void leftmove(deque<int> &circlequeue, int select, int &sw)
{
	// 비교, 찾는 원소이면 지우기만 하고, 찾았음을 알려줌.
	if (circlequeue.front() == select)
	{
		// 큐의 맨 앞에 있던 원소를 지움
		circlequeue.erase(circlequeue.begin());
		sw = 1;
	}
	else // 찾는 원소가 아니면, 큐의 맨 앞에 있던 원소를 큐의 맨 뒤로 보냄
	{
		int temp = circlequeue.front();
		circlequeue.erase(circlequeue.begin());
		circlequeue.push_back(temp);
	}
	return;
}

void rightmove(deque<int> &circlequeue, int select, int &sw)
{
	// 비교, 찾는 원소이면 지우기만 하고, 찾았음을 알려줌
	if (circlequeue.front() == select)
	{
		// 큐의 맨 앞에 있던 원소를 지움
		circlequeue.erase(circlequeue.begin());
		sw = 1;
	}
	else // 찾는 원소가 아니면, 큐의 맨 뒤에 있던 원소를 큐의 맨 앞으로 보냄
	{
		int temp = circlequeue.back();
		circlequeue.pop_back();
		circlequeue.push_front(temp);
	}
	return;
}