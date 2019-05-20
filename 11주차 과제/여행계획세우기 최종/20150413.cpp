#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// 그래프를 배열로 나타내는 방법 사용불가(시간 초과)
// int graph[10000][10000] = { 0 , };


// 그래프를 인접 리스트로 나타내려고 함
vector<vector<int> > graph;			// graph의 경우 입력된 그래프 값을 보관
vector<vector<int> > backgraph;		// backgraph의 경우 graph의 reverse버전

vector<vector<int> > scc_set;		// scc_set의 경우 SCC 하나가 속한 node들을 보관
vector<int> scc_Index;				// scc_Index의 경우 SCC의 전체적인 index를 보관

// SCC를 구할 때 사용하는 stack으로,
// SCC를 구할 때는 dfs 함수와 stack을 사용하여 O(V+E)만에 구한다.
stack<int> scc_st;

// dfs 함수
void dfs(int here, vector<bool> &visited) {
	visited[here] = true;
	// 모든 정점에 대해서 탐색함
	for (int i : graph[here]) {
		if (!visited[i])
			dfs(i, visited);
	}
	// scc_st에 push함
	scc_st.push(here);
}

// reverse된 dfs 함수, dfs함수와 거의 동일
void back_dfs(int here, vector<bool> &visited, vector<int> &path) {
	visited[here] = true;
	path.push_back(here); // path에 push함 이러면 경로를 알 수 있음
	for (int i : backgraph[here]) {
		if (!visited[i]) {
			back_dfs(i, visited, path);
		}
	}
}

// 위상 정렬을 수행하는 함수 - Topological_Sort(memoization 기법 사용)
int Topological_Sort(const vector<vector<int> > &graph, const vector<int> &vertex, vector<int> &DP, int here, int last) {
	if (here == last)
		return vertex[here];

	int &ret = DP[here];

	if (ret != -9999999)	// 만약 초기값이 아니라면, 이미 탐색했다는 것이므로
		return ret;		// ret을 반환 (memoization 기법)

	for (int next : graph[here]) {
		// 시작점에서 이 SCC에 도달 가능해야만, next의 정보를 갱신한다.
		// 이는 재귀호출로 올라가는 memoization으로 처리한다.
		ret = max(ret, Topological_Sort(graph, vertex, DP, next, last) + vertex[here]);
	}

	return ret;
}


int main() {

	/************************** 초기화 ************************************/

	// N : 여행하려는 도시 개수 
	// M : 비행로 개수
	// S : 시작 도시
	// T : 도착 도시
	int N, M, S, T;
	cin >> N >> M >> S >> T;

	// 그래프의 크기 조정
	graph.resize(N);
	backgraph.resize(N);
	scc_Index.resize(N, -1);

	// 그래프의 정보를 입력받아서 저장함
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;

		u--; v--;	// vector의 index는 0부터이므로, 1을 빼줌
		graph[u].push_back(v);		// u -> v
		backgraph[v].push_back(u);		// v -> u
	}
	// 같은 이유로, index가 0부터이기 때문에 1을 빼줌
	S--, T--;


	/******************* SCC로 묶는 과정 ****************************/

	// SCC로 묶는 과정 시행
	// 방문했는지 안했는지 여부를 검사하기 위한 vector 선언 (방문했으면 true)
	vector<bool> visited(N, false);
	for (int i = 0; i < N; i++) {
		if (!visited[i])
			dfs(i, visited);
	}

	// 반대로 탐색했을 때, 자신 또는 자신의 자손들이 도달 가능한 제일 높은 정점이 자신이라면
	// SCC가 추출된다.
	// 따라서 반대로 탐색했을 때 방문했는지 안했는지 여부를 검사하기 위한 vector를 선언한다.
	vector<bool> rvisited(N, false);
	while (!scc_st.empty()) {
		int temp = scc_st.top();
		scc_st.pop();
		if (!rvisited[temp]) {
			vector<int> path;
			back_dfs(temp, rvisited, path);
			for (int i : path) {
				scc_Index[i] = scc_set.size();	// 그 경로를 모아 하나의 SCC로 만든다.
			}
			scc_set.push_back(path);			// 이렇게 하면 하나의 SCC완성!
		}
	}

	// 위상 정렬을 시행하는 부분
	vector<vector<int> > cgraph(scc_set.size());	// 각 SCC의 결과값을 저장함
	vector<int> vertex(scc_set.size());				// vertex를 저장할 vector 선언

	// DFS를 하며 SCC를 추출한다.
	for (int i = 0; i < scc_set.size(); i++) {
		for (int j = 0; j < scc_set[i].size(); j++) {
			for (int k = 0; k < graph[scc_set[i][j]].size(); k++) {
				int v = scc_Index[graph[scc_set[i][j]][k]];
				if (i == v || v == -1) continue;
				cgraph[v].push_back(i);
			}
		}

		// 출력을 위해 SCC들을 정렬한다.
		sort(cgraph[i].begin(), cgraph[i].end());

		// 그리고 나서, 중복되는 것은 하나로 치므로 중복되는 것을 제거한다.
		cgraph[i].erase(unique(cgraph[i].begin(), cgraph[i].end()), cgraph[i].end());

		vertex[i] = scc_set[i].size();
	}
	visited[scc_Index[S]] = true;

	// 최대로 방문할 수 있는 도시의 개수를 구하자.
	vector<int> DP(scc_set.size(), -9999999);
	int answer = Topological_Sort(cgraph, vertex, DP, scc_Index[T], scc_Index[S]);

	// 하나도 방문할 수 없는 경우 예외처리
	if (answer <= 0) {
		cout << 0;
	}
	else {
		cout << answer;
	}
}