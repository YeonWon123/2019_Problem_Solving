#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// �׷����� �迭�� ��Ÿ���� ��� ���Ұ�(�ð� �ʰ�)
// int graph[10000][10000] = { 0 , };


// �׷����� ���� ����Ʈ�� ��Ÿ������ ��
vector<vector<int> > graph;			// graph�� ��� �Էµ� �׷��� ���� ����
vector<vector<int> > backgraph;		// backgraph�� ��� graph�� reverse����

vector<vector<int> > scc_set;		// scc_set�� ��� SCC �ϳ��� ���� node���� ����
vector<int> scc_Index;				// scc_Index�� ��� SCC�� ��ü���� index�� ����

// SCC�� ���� �� ����ϴ� stack����,
// SCC�� ���� ���� dfs �Լ��� stack�� ����Ͽ� O(V+E)���� ���Ѵ�.
stack<int> scc_st;

// dfs �Լ�
void dfs(int here, vector<bool> &visited) {
	visited[here] = true;
	// ��� ������ ���ؼ� Ž����
	for (int i : graph[here]) {
		if (!visited[i])
			dfs(i, visited);
	}
	// scc_st�� push��
	scc_st.push(here);
}

// reverse�� dfs �Լ�, dfs�Լ��� ���� ����
void back_dfs(int here, vector<bool> &visited, vector<int> &path) {
	visited[here] = true;
	path.push_back(here); // path�� push�� �̷��� ��θ� �� �� ����
	for (int i : backgraph[here]) {
		if (!visited[i]) {
			back_dfs(i, visited, path);
		}
	}
}

// ���� ������ �����ϴ� �Լ� - Topological_Sort(memoization ��� ���)
int Topological_Sort(const vector<vector<int> > &graph, const vector<int> &vertex, vector<int> &DP, int here, int last) {
	if (here == last)
		return vertex[here];

	int &ret = DP[here];

	if (ret != -9999999)	// ���� �ʱⰪ�� �ƴ϶��, �̹� Ž���ߴٴ� ���̹Ƿ�
		return ret;		// ret�� ��ȯ (memoization ���)

	for (int next : graph[here]) {
		// ���������� �� SCC�� ���� �����ؾ߸�, next�� ������ �����Ѵ�.
		// �̴� ���ȣ��� �ö󰡴� memoization���� ó���Ѵ�.
		ret = max(ret, Topological_Sort(graph, vertex, DP, next, last) + vertex[here]);
	}

	return ret;
}


int main() {

	/************************** �ʱ�ȭ ************************************/

	// N : �����Ϸ��� ���� ���� 
	// M : ����� ����
	// S : ���� ����
	// T : ���� ����
	int N, M, S, T;
	cin >> N >> M >> S >> T;

	// �׷����� ũ�� ����
	graph.resize(N);
	backgraph.resize(N);
	scc_Index.resize(N, -1);

	// �׷����� ������ �Է¹޾Ƽ� ������
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;

		u--; v--;	// vector�� index�� 0�����̹Ƿ�, 1�� ����
		graph[u].push_back(v);		// u -> v
		backgraph[v].push_back(u);		// v -> u
	}
	// ���� ������, index�� 0�����̱� ������ 1�� ����
	S--, T--;


	/******************* SCC�� ���� ���� ****************************/

	// SCC�� ���� ���� ����
	// �湮�ߴ��� ���ߴ��� ���θ� �˻��ϱ� ���� vector ���� (�湮������ true)
	vector<bool> visited(N, false);
	for (int i = 0; i < N; i++) {
		if (!visited[i])
			dfs(i, visited);
	}

	// �ݴ�� Ž������ ��, �ڽ� �Ǵ� �ڽ��� �ڼյ��� ���� ������ ���� ���� ������ �ڽ��̶��
	// SCC�� ����ȴ�.
	// ���� �ݴ�� Ž������ �� �湮�ߴ��� ���ߴ��� ���θ� �˻��ϱ� ���� vector�� �����Ѵ�.
	vector<bool> rvisited(N, false);
	while (!scc_st.empty()) {
		int temp = scc_st.top();
		scc_st.pop();
		if (!rvisited[temp]) {
			vector<int> path;
			back_dfs(temp, rvisited, path);
			for (int i : path) {
				scc_Index[i] = scc_set.size();	// �� ��θ� ��� �ϳ��� SCC�� �����.
			}
			scc_set.push_back(path);			// �̷��� �ϸ� �ϳ��� SCC�ϼ�!
		}
	}

	// ���� ������ �����ϴ� �κ�
	vector<vector<int> > cgraph(scc_set.size());	// �� SCC�� ������� ������
	vector<int> vertex(scc_set.size());				// vertex�� ������ vector ����

	// DFS�� �ϸ� SCC�� �����Ѵ�.
	for (int i = 0; i < scc_set.size(); i++) {
		for (int j = 0; j < scc_set[i].size(); j++) {
			for (int k = 0; k < graph[scc_set[i][j]].size(); k++) {
				int v = scc_Index[graph[scc_set[i][j]][k]];
				if (i == v || v == -1) continue;
				cgraph[v].push_back(i);
			}
		}

		// ����� ���� SCC���� �����Ѵ�.
		sort(cgraph[i].begin(), cgraph[i].end());

		// �׸��� ����, �ߺ��Ǵ� ���� �ϳ��� ġ�Ƿ� �ߺ��Ǵ� ���� �����Ѵ�.
		cgraph[i].erase(unique(cgraph[i].begin(), cgraph[i].end()), cgraph[i].end());

		vertex[i] = scc_set[i].size();
	}
	visited[scc_Index[S]] = true;

	// �ִ�� �湮�� �� �ִ� ������ ������ ������.
	vector<int> DP(scc_set.size(), -9999999);
	int answer = Topological_Sort(cgraph, vertex, DP, scc_Index[T], scc_Index[S]);

	// �ϳ��� �湮�� �� ���� ��� ����ó��
	if (answer <= 0) {
		cout << 0;
	}
	else {
		cout << answer;
	}
}