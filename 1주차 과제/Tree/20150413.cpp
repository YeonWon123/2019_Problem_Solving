#include <iostream>
#include <vector>
using namespace std;

// #define DEBUG

// 트리의 노드를 나타냄
typedef struct nodes{
	int number; // 숫자
	int height; // 노드 높이
	struct nodes *prev; // 부모 노드
	struct nodes *next1; // 자식 노드1
	struct nodes *next2; // 자식 노드2
	nodes()
	{
		prev = NULL;
		next1 = NULL;
		next2 = NULL;
	}
} node;

// 격자 모양의 틀 안에 각 노드들을 기입하는 구조체
// 각 노드의 주소를 보관
typedef struct lattices {
	node *node_pointer;
} lattice;

// 각 트리의 레벨과 그 너비를 보관하는 구조체
typedef struct level_widths{
	int level;
	int start_node;
	int end_node;
	int width;
} level_width;


// 함수 원형 선언
// 전위 순회 함수 (재귀 호출 이용)
void preorder(node *tree, int parent_num, int height);
// 중위 순회 함수 (재귀 호출 이용)
void inorder(node *tree, lattice *lattice, int parent_num, int &width_num);


int main()
{
	int N; // 노드의 개수
	cin >> N;

	// 1. 부모 노드와 자식 노드 간의 관계를 정리하여 트리를 만든다.

	// tree[0]은 쓰지 않고, tree[1]부터 tree[N]까지 사용할 예정
	node *tree = new node[N+1];
	for (int i = 1; i <= N; i++)
	{
		tree[i].number = i;
	}
	
	// 노드의 개수만큼 반복
	for (int i = 1; i <= N; i++)
	{
		// 부모 노드, 자식 노드1, 자식 노드2
		int parent, child1, child2;
		cin >> parent >> child1 >> child2;

		// 자식 노드1이 -1이 아닐 경우, 부모 노드와 자식 노드1을 연결
		if (child1 != -1)
		{
			tree[parent].next1 = &tree[child1];
			tree[child1].prev = &tree[parent];
		}

		// 자식 노드2가 -1이 아닐 경우, 부모 노드와 자식 노드2를 연결
		if (child2 != -1)
		{
			tree[parent].next2 = &tree[child2];
			tree[child2].prev = &tree[parent];
		}
	}

	// debug
#ifdef DEBUG
	for (int i = 1; i <= N; i++)
	{
		cout << tree[i].number << " ";
		if (tree[i].next1 == NULL)
			cout << -1 << " ";
		else cout << tree[i].next1->number << " ";

		if (tree[i].next2 == NULL)
			cout << -1 << " ";
		else cout << tree[i].next2->number << " ";

		if (tree[i].prev == NULL)
			cout << -1 << endl;
		else cout << tree[i].prev->number << endl;
	}
#endif

	// 2. 만들어진 이진 트리를 규칙에 따라 왼쪽에서 오른쪽으로 숫자를 나열해 보자

	// 먼저 전위 순회에서 제일 먼저 탐색되는 루트 노드를 찾는다.
	// 루트 노드는 어떤 노드에서 출발해도 찾을 수 있다.
	// 왜냐하면, 루트 노드만이 부모 노드가 NULL이기 때문이다.
	int root_num = 1;
	while (1)
	{
		if (tree[root_num].prev == NULL)
			break;

		root_num = tree[root_num].prev->number;
	}
	
	// 격자 모양의 틀 안에 각 노드들을 기입하는 구조체
	// 격자 모양에서 열 번호는 lattice[i]에서 i가 될 것이다.
	// 격자 모양에서 행 번호는 tree[i].height가 될 것이다.
	lattice *latticeboard = new lattice[N+1];


	// 전위 순회를 통해서 이진 트리의 각 노드에 높이를 부여한다.
	preorder(tree, root_num, 1);
	
	// 중위 순회를 통해서 이진 트리를 왼쪽에서 오른쪽으로 나열한다.
	int width_num = 1;
	inorder(tree, latticeboard, root_num, width_num);
	
#ifdef DEBUG
	// debug
	for (int i = 1; i <= N; i++)
	{
		cout << latticeboard[i].node_pointer->number << " ";
	}
	cout << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << latticeboard[i].node_pointer->height << " ";
	}
	cout << endl;
#endif

	// 3. 격자 판에 노드를 채워 넣었으니 이제 너비를 계산해 보자.
	vector<level_width> data;

	for (int i = 1; i <= N; i++)
	{
		int sw = 0;
		for (unsigned int j = 0; j < data.size(); j++)
		{
			// 만약 기존에 data[j].level 안에 그 높이(레벨)이 있다면
			// 이미 한 번 입력받은 적이 있다는 이야기이다.
			// 그렇다면 end_node에 열 번호인 i를 할당한다.
			if (data[j].level == latticeboard[i].node_pointer->height )
			{
				data[j].end_node = i;
				sw = 1;
				break;
			}
		}

		// sw가 0이면 그 높이(레벨)가 data 안에 없다는 뜻이니
		// 그 높이(레벨)에 대해 새로 push를 해 준다.
		// 높이는 level에 latticeboard[i].node_pointer->height를 할당한다.
		// start_node에는 열 번호인 i값을 할당하고 end_node는 0으로 한다.
		// 너비는 이 for문을 빠져나가서, 마지막에 계산한다. (일단은 1으로 둠)
		if (sw == 0)
		{
			data.push_back({ latticeboard[i].node_pointer->height,
			i, 0, 1 });
		}
	}

#ifdef DEBUG
	// debug
	cout << endl << "3번 시작" << endl;
	for (unsigned int i = 0; i < data.size(); i++)
	{
		cout << data[i].level << " " << data[i].start_node << " " 
			<< data[i].end_node << endl;
	}
#endif

	// 각 높이(너비)에 대해 너비를 계산한다. 
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].width = data[i].end_node - data[i].start_node + 1;
		if (data[i].width <= 0) data[i].width = 1;
#ifdef DEBUG
		cout << data[i].level << " " << data[i].width << endl;
#endif
	}

	// 이제 너비가 가장 넓은 레벨을 저장하는 변수들을 두고,
	// 이 변수를 갱신해 최종 답을 출력한다.
	int wide_level = 10001; // 너비가 가장 넓은 레벨 (엄청 큰 수로 두기)
	int wide = 1;			 // 그 레벨의 너비		(가장 작은 자연수로 두기)

	for (unsigned int i = 0; i < data.size(); i++)
	{
		// 만약 지금 계산한 너비가 더 넓으면 바꾸고,
		if (wide < data[i].width)
		{
			wide_level = data[i].level;
			wide = data[i].width;
		}
		else if (wide == data[i].width) // 같으면
		{
			// 높이가 더 낮은지 확인
			if (wide_level > data[i].level)
			{
				// 낮으면 갱신
				wide_level = data[i].level;
				wide = data[i].width;
			}
		}
	}
	cout << wide_level << " " << wide;
	
	return 0;
}

// 전위 순회 함수 (재귀 호출 이용)
void preorder(node *tree, int parent_num, int height)
{
	tree[parent_num].height = height;

	if (tree[parent_num].next1 != NULL)
	{
		preorder(tree, tree[parent_num].next1->number, height + 1);
	}

	if (tree[parent_num].next2 != NULL)
	{
		preorder(tree, tree[parent_num].next2->number, height + 1);
	}
}

// 중위 순회 함수 (재귀 호출 이용)
void inorder(node *tree, lattice *latticeboard, int parent_num, int &width_num)
{
	if (tree[parent_num].next1 != NULL)
	{
		inorder(tree, latticeboard, tree[parent_num].next1->number, width_num);
	}

	latticeboard[width_num].node_pointer = &tree[parent_num];
	width_num++;
	
	if (tree[parent_num].next2 != NULL)
	{
		inorder(tree, latticeboard, tree[parent_num].next2->number, width_num);
	}

}