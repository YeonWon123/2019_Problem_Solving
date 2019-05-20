#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 각각의 비행로에 대한 정보
pair <int, int> road[100000];

// 그래프를 배열로 나타내는 방법 사용불가(시간 초과)
// int graph[10000][10000] = { 0 , };

// 인접 리스트 사용
vector<vector<int>> graph;

// 방문했는지 안했는지 여부를 검사하기 위한 배열 선언 (방문했으면 1)
int visit[10001] = { 0, };

// SCC를 뽑아내기 위한 class 정의
// 한 번의 DFS와 별도의 stack을 사용하여 그래프에서 SCC들을 분리한다.
class SCC {

public:
	int V, E;				// V, E : 그래프의 Vertex, Edge
	int cnt, dfsn[10001];	// dfs를 돌려서, 그 정점에서 dfs를 돌린 값을 기록
	int SN, sn[10001];		// SN: SCC 개수, sn[i]: i가 속한 SCC의 번호
	vector<int> adj[10001];
	bool finished[10001];	// SCC 분리가 끝난 정점만 true

	stack<int> S;
	vector<vector<int>> SCC;

public:

	// 자신의 결과값을 리턴하는 DFS 함수
	int DFS(int curr) {

		dfsn[curr] = ++cnt; // dfsn 결정
		S.push(curr);		// 스택에 자신을 push

		// 자신의 dfsn, 자식들의 결과나 dfsn 중 가장 작은 번호를 result에 저장
		int result = dfsn[curr];
		for (int next : adj[curr]) {
			// 아직 방문하지 않은 이웃
			if (dfsn[next] == 0) result = min(result, DFS(next));
			// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
			else if (!finished[next]) result = min(result, dfsn[next]);
		}

		// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
		if (result == dfsn[curr]) {
			vector<int> currSCC;

			// 스택에서 자신이 나올 때까지 pop
			while (1) {
				int t = S.top();
				S.pop();
				currSCC.push_back(t);
				finished[t] = true;
				sn[t] = SN;
				if (t == curr) break;
			}

			// 출력을 위해 원소 정렬
			sort(currSCC.begin(), currSCC.end());

			// SCC 추출
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

	// 인접 리스트 크기 조정
	graph.reserve(N+1); // index를 1부터 N까지 사용할 예정
	
	for (int i = 0; i < M; i++) {
		cin >> road[i].first >> road[i].second;
		graph[road[i].first].push_back(road[i].second); // 인접 리스트처럼 할당
	}

	// Strongly Connected Components(SCC) 적용

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