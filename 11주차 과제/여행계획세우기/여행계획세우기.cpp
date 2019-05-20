#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// ������ ����ο� ���� ����
pair <int, int> road[100000];

// �׷����� �迭�� ��Ÿ���� ��� ���Ұ�(�ð� �ʰ�)
// int graph[10000][10000] = { 0 , };

// ���� ����Ʈ ���
vector<vector<int>> graph;

// �湮�ߴ��� ���ߴ��� ���θ� �˻��ϱ� ���� �迭 ���� (�湮������ 1)
int visit[10001] = { 0, };

// SCC�� �̾Ƴ��� ���� class ����
// �� ���� DFS�� ������ stack�� ����Ͽ� �׷������� SCC���� �и��Ѵ�.
class SCC {

public:
	int V, E;				// V, E : �׷����� Vertex, Edge
	int cnt, dfsn[10001];	// dfs�� ������, �� �������� dfs�� ���� ���� ���
	int SN, sn[10001];		// SN: SCC ����, sn[i]: i�� ���� SCC�� ��ȣ
	vector<int> adj[10001];
	bool finished[10001];	// SCC �и��� ���� ������ true

	stack<int> S;
	vector<vector<int>> SCC;

public:

	// �ڽ��� ������� �����ϴ� DFS �Լ�
	int DFS(int curr) {

		dfsn[curr] = ++cnt; // dfsn ����
		S.push(curr);		// ���ÿ� �ڽ��� push

		// �ڽ��� dfsn, �ڽĵ��� ����� dfsn �� ���� ���� ��ȣ�� result�� ����
		int result = dfsn[curr];
		for (int next : adj[curr]) {
			// ���� �湮���� ���� �̿�
			if (dfsn[next] == 0) result = min(result, DFS(next));
			// �湮�� ������ ���� SCC�� ��������� ���� �̿�
			else if (!finished[next]) result = min(result, dfsn[next]);
		}

		// �ڽ�, �ڽ��� �ڼյ��� ���� ������ ���� ���� ������ �ڽ��� ��� SCC ����
		if (result == dfsn[curr]) {
			vector<int> currSCC;

			// ���ÿ��� �ڽ��� ���� ������ pop
			while (1) {
				int t = S.top();
				S.pop();
				currSCC.push_back(t);
				finished[t] = true;
				sn[t] = SN;
				if (t == curr) break;
			}

			// ����� ���� ���� ����
			sort(currSCC.begin(), currSCC.end());

			// SCC ����
			SCC.push_back(currSCC);
			SN++;
		}
		return result;
	}

};

SCC scc;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N, M, S, T;
	cin >> N >> M >> S >> T;

	// ���� ����Ʈ ũ�� ����
	graph.reserve(N+1); // index�� 1���� N���� ����� ����
	
	for (int i = 0; i < M; i++) {
		cin >> road[i].first >> road[i].second;
		graph[road[i].first].push_back(road[i].second); // ���� ����Ʈó�� �Ҵ�
	}

	// Strongly Connected Components(SCC) ����

	/*
	for (int i = 0; i < N; i++) {
		if (visit[i] == 0) {
			scc.DFS(i);
		}
		while (!st.empty()) {
			int here = st.top();
			st.pop();
			if (!rvisited[here]) {
				vector<int> path;
				rdfs(here, rvisited, path);
				for (int j = 0; j < path; j++) {
					sccIdx[j] = compress.size();
				}
				compress.push_back(path)
			}
		}
	}
	*/

	return 0;
}