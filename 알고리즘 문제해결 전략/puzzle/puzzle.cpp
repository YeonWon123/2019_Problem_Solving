#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() 함수 사용
#include <conio.h> //getch()와 kbhit() 함수 사용
#include <ctime> //clock() 함수 사용

using namespace std;

#define ESC 27 //게임 종료
#define LEFT 75 //왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80 //아래 화살표 키 ASCII값
#define UP 72 //위쪽 화살표 키 ASCII값

#define DIM 4 //4x4 퍼즐맵의 크기

static int x, y; //빈칸의 위치
static int moveNum; //이동회수
static clock_t sTime; //시작 시간
static clock_t cTime; //시작 시간

//게임 Map 그리기 시작 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define MAP_STARTX 20 
#define MAP_STARTY 2

//이동 회수 및 소요시간 출력 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define SCORE_STARTX 20
#define SCORE_STARTY 12



enum COMMAND { Stop = 0, Left, Right, Down, Up, Non };

void gotoXY(int x, int y); //콘솔 화면에서 커서를 특정 위치로 이동
void init(int(*map)[DIM]); //초기화 함수; 필요시에 매개변수를 추가함
void gameDraw(int(*map)[DIM]); // 게임 맵과 반복회수, 시간 출력함수; MAP_STARTX, MAP_STARTY 상수를 참조해서 항상 고정 위치(gotoXY함수 사용에 출력필요시에 매개변수를 추가함
//                화면 출력 예시
//                Fifteen Puzzle
//                  1  2  9  3
//                  6  8  7  4
//                  10    5  15
//                  13 14 12 11
//
//                  이동 회수: 10회
//                  소요 시간: 15.2초

void puzzleMove(int(*map)[DIM], int action); //퍼즐 이동 함수; 필요시에 매개변수 추가함
void shuffle(int num, int(*map)[DIM]);//퍼즐 맵 초기화; 50회 무작위 이동, 필요시에 인자 추가 할 수 있음
int getAction(int(*map)[DIM]);//모든 퍼즐이 제 위치에 있거나 ESC키가 눌러졌으면 정수 0을 반환
				   // 방향키를 눌렀을 때는 해당 키값을 반환(LEFT, RIGHT, DOWN, UP)
				   //필요시에 매개변수 인자를 추가할 수 있음

int getDirectKey()
{
	char key = Non;
	if (_kbhit() != 0) //키보드를 눌렀는지 확인함
	{
		//특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값은 224값을 발생하고 두번째 값은 특수키에 따라 다름
		//특수 키를 확인하기 위해 2번의 getch()함수를 호출해야 함
		key = getch();
		if (key == 224) key = _getch();
	}
	return key;
}


int main(void)
{
	int map[DIM][DIM];
	int action = Non;

	init(map);
	shuffle(50, map);
	gameDraw(map);
	action = getAction(map);
	while (action)
	{
		puzzleMove(map, action);
		gameDraw(map);
		action = getAction(map);
	}

	cout << "The game is stopped" << endl;
	return 0;
}

void init(int(*map)[DIM])
{
	int num = 1;

	//map 초기화
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			map[i][j] = num++;
	map[DIM - 1][DIM - 1] = 0;

	//현재시간 획득
	sTime = cTime = clock();
	x = y = 3; //0의 좌표값 
	srand(time(NULL));
}

void shuffle(int num, int(*map)[DIM])
{
	int temp;

	for (int i = 0; i < num; i++)
	{
		temp = rand() % 4 + 1;
		puzzleMove(map, temp);
		gameDraw(map);
		Sleep(100);
	}
}

void gameDraw(int(*map)[DIM])
{
	gotoXY(MAP_STARTX, MAP_STARTY);
	cout << "   Fifteen Puzzle" << endl;

	for (int i = 0; i < DIM; i++)
	{
		gotoXY(MAP_STARTX, MAP_STARTY + i * 2 + 2);
		for (int j = 0; j < DIM; j++)
		{
			if (map[i][j] != 0)
			{
				cout.width(4);
				cout << map[i][j];
			}
			else
			{
				cout.width(4);
				cout << '*';
			}
		}
		cout << endl;
	}

	cout << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY);
	cout << "  이동 회수: " << moveNum << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY + 1);
	cTime = clock();
	cout << "  소요 시간: " << (cTime - sTime) / 1000.0 << "초" << endl;
}



void puzzleMove(int(*map)[DIM], int action)
{

	switch (action)
	{
	case Left:
		if (x > 0)  // 좌측 경계에 도달했는지 체크, 경계에 도달하면 퍼즐을 위치를 바꾸지 않음
		{
			x--;
			int temp = map[y][x];
			map[y][x] = map[y][x + 1];
			map[y][x + 1] = temp;
			moveNum++;
		}
		break;
	case Right:
		if (x < DIM - 1) //우측 경계에 도달했는지 체크, 경계에 도달하면 퍼즐을 위치를 바꾸지 않음
		{
			x++;
			int temp = map[y][x];
			map[y][x] = map[y][x - 1];
			map[y][x - 1] = temp;
			moveNum++;
		}
		break;
	case Up:
		if (y > 0) //상단 경계에 도달햇는지 체크, 경계에 도달하면 퍼즐을 위치를 바꾸지 않음
		{
			y--;
			int temp = map[y][x];
			map[y][x] = map[y + 1][x];
			map[y + 1][x] = temp;
			moveNum++;
		}
		break;
	case Down:
		if (y < DIM - 1) // 하단 경계에 도달했는지 체크, 경계에 도달하면 퍼즐을 위치를 바꾸지 않음 
		{
			y++;
			int temp = map[y][x];
			map[y][x] = map[y - 1][x];
			map[y - 1][x] = temp;
			moveNum++;
		}
	}
}

int getAction(int(*map)[DIM])
{
	int num = 1, command;

	// 퍼즐이 완성되었는지 확인
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (map[i][j] != num++)
				break;
	if (num > DIM*DIM)  //마지막까지 확인되면 퍼즐이 완성됨
		return Stop;


	//방향키에 따라 명령어를 설정
	switch (getDirectKey())
	{
	case LEFT:
		command = Left;
		break;
	case RIGHT:
		command = Right;
		break;
	case UP:
		command = Up;
		break;
	case DOWN:
		command = Down;
		break;
	case ESC:
		command = Stop;
		break;
	default:
		command = Non; // 방향키나 ESC키 외에 다른 키가 눌러지면 아무 명령어도 수행하지 않음
	}

	return command;
}


//콘솔 화면에서 커서를 특정 위치로 이동
void gotoXY(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 그외 함수들을 정의함
