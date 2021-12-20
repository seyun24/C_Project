#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <stdbool.h>// bool 타입 사용가능하게 함
#pragma comment(lib, "winmm.lib")//노래 재생을 도와주는 전처리기
#pragma warning(disable:4996)//_를 안달아도됨 file 입력 할때 쓰려고 넣었음

#define RED 4
#define BLUE 1
#define YELLOW 6
#define GREEN 2
#define PUPLE 5
#define WHITE 7
#define GREY 8
#define p 112 //일시정지 

#define ESC 27 //콘솔 종료


clock_t startDropT, endT, startGroundT;//long형을 다른이름으 typedef한것으로 time.h 헤더파일이 있어야 사용가능 
//블록이 이동한 그순간,블록이 땅에 닿았을때에 시간, 
int x = 8, y = 0;//기본 좌표
//RECT blockSize;
int blockForm;//블록형태 7가지
int blockRotation = 0;//블록 돌리기 4가지 형태
int key;//keybord ???
int speed = 800;//블럭 떨어지는 속도 조절 변수 clock함수에서는 1000클락을 1초라 생각하기에 0.8초 ??? 

int block[7][4][4][4] = {//7개의 형태, 4개의 회전,블럭의 모양을 그릴 2차원배열
	{ // T모양 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭 반대
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭 반대
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};


int space[16][12] = { //게임이 실행될 메인화면을 나타내는 2차원배열 0은 빈화면 1은 벽을 나타냄
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

int CopyMap[16][12] = {  //게임을 리셋하고 다시 시작할때 space에 있는 값을 초기값을 바꾸어 게임을 초기화시키는 용도
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};



void Init();//초기 세팅
void gotoxy(int x, int y);//커서를 움직이는 함수
void CreateRandomForm();//형태와 컬러가 다른 블록 호출될때마다 생성
bool CheckCrash(int x, int y);//충돌 관리해주는 함수(미완)
void DropBlock();//블록의 하강속도 조절 함수
void BlockToGround();//블록이 바닥과 닿은후의 처리되는 호출수행
void RemoveLine();//줄이 채워졌을때 해당줄을 지우고 블록을 이동시키는 함수
void DrawMap();//space를 반영하여 게임판을 그림
void DrawBlock();//block배열을 참고하여 해당 block을 출력하는 함수
void InputKey();//keybord의 입력을 받아오고 해당 키에 맞는 문장실행 
bool GameOver();//게임오버 체크
void ResetGame();//맵 리셋
void SecondS();//메인화면 옆 화면
void game_over();//게임오버 스크린
void reset_score();//점수 초기화 및 갱신



int color;
int score = 0;


int last_score = 0; //마지막게임점수 
int best_score = 0; //최고게임점수 
int main() {
    one://goto구문 레이블 리셋후 one으로 이동
	
	Init();//초기상태
	startDropT = clock();//클락 함수 사용 1000클락이 1초 시작점 체크
	
	color = 1;
	reset_score();//전판 점수 초기화 및 갱신
	while (_kbhit() == 0) {//색깔을 계속 바꾸고 배경을 틀기위해서 반복문 사용! 
		PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);//start.wav참조해서 일반재상 모드로 재생
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color % 16);	
		gotoxy(0, 0); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(100); //window.h참조 윈도우 os 제공하는 api함수 1000 == 1초
		gotoxy(0, 1); printf("■■▤▤▤■■▤▤▤■■▤▤▤■■▤▤▤■■■▤■■■▤▤■■"); Sleep(100); //문장마다 0.1초씩 간격을 넣음으로써 물결처럼 보임
		gotoxy(0, 2); printf("■■■▤■■■▤■■■■■▤■■■▤■■▤■■▤■■▤■■■■"); Sleep(100); //와일문 때문에 계속해서 프린트 되기때문에 좌표를 고정시켜야됨 
		gotoxy(0, 3); printf("■■■▤■■■▤▤▤■■■▤■■■▤▤▤■■■▤■■■▤■■■"); Sleep(100); //그래서 gotoxy로 고정
		gotoxy(0, 4); printf("■■■▤■■■▤■■■■■▤■■■▤■▤■■■▤■■■■▤■■"); Sleep(100); 
		gotoxy(0, 5); printf("■■■▤■■■▤▤▤■■■▤■■■▤■■▤■■▤■■▤▤■■■"); Sleep(100); 
		gotoxy(0, 6); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(100); 
		gotoxy(0, 7); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(100); 
		gotoxy(0, 8); printf("                                   project by 202104016 박세윤"); Sleep(100); 
		gotoxy(9, 11);  printf("      press any key to start");
		
		for (int z = 0; z < 50; z++) {//물결화면 출력후 화면지연시키기 총 1.5초
			Sleep(30); //0.03초씩 
			if (_kbhit()) break;//여기다 굳이 넣는 이유는 지연시간을 기달리고 넘어가기 때문에 부자연스러워서 지연없이 눌럿을때 넘어가기 위함!
		}
		color++;
		if (color % 16 == 0)//색깔 로직
			color++;
		
	}
	getch();//남은 버퍼를 받음으로써 아무키를 눌렀을때 메인화면에 영향을 주지않게 함
	CreateRandomForm();//실행시 처음 블록 형성
	while (GameOver()) {//게임오버 여부를 체크하여 게임오버되면 반복문 탈출!
		//무한반복을 해야 화면이 반영되기 때문에 반복사용!
		DrawMap();//기본적인 화면을 그린다
		DrawBlock();//움직일 블록을 그린다
		DropBlock();//떨어지는 블록의 움직임을 구현
		BlockToGround();//블록이 땅에 닿았을시 처리
		RemoveLine();//한줄이 채워지면 제거후 줄바꿈
		InputKey();//키보드의 입력을 받고 해당문장 실행
		SecondS();//메인화면 옆에 띄어져 있는 정보창
		
	}
	
	system("cls");//메인 화면을 지워줌


	game_over();//게임오버 스크린 출력
		

	system("cls");//게임 오버 화면 지워줌
	 
	ResetGame();//게임 초기화
	goto one;//처음으로 레이블 >one
	return 0;
}
bool GameOver() {//2차원배열 space의 첫번째 행에 2라는 값이 하나라도 들어오면 게임종료
	for (int j = 0; j < 12; j++) {
		if (space[0][j] == 2) {//0번째만 체크하면됨 
			return false;
		}
		else true;
	}
}
void ResetGame() {//출력됫던 메인화면을 원래형태로 초기화(메인화면 초기화)
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			space[i][j] = CopyMap[i][j]; //초기의 배열의 원소를 똑같이 가지는 CopyMap을 space에 복사
		}
	}
}
void reset_score(void) {//점수 초기화 및 갱신
	score = 0;//score를 0으로
	
	FILE* file = fopen("score.txt", "rt"); // score.dat파일을 연결 
	if (file == 0) { best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
	else {
		fscanf(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
		fclose(file); //파일 닫음 
	}
}
void game_over()//game over 스크린
{
	
	PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);//gameover.wav 일반재생모드로 재생
	if (score > best_score) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	}
	else 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //게임오버 메세지 
	gotoxy(x, y + 1); printf("▤                              ▤");
	gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
	gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 5); printf("▤   YOUR SCORE: %6d         ▤", score*100);//점수 1당 100점
	gotoxy(x, y + 6); printf("▤                              ▤");
	gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
	gotoxy(x, y + 8); printf("▤                              ▤");
	gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	last_score = score; //최근점수를 저장 
	if (score > best_score) { //최고기록 갱신시 
		
		FILE* file = fopen("score.txt", "wt"); //score.txt에 점수 저장                
		PlaySound(TEXT("clip.wav"), NULL, SND_ASYNC);//clip.wav 일반모드로 재생
		while (kbhit() == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);//초록색 컬러 지정
			gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  "); Sleep(150);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//하양색 컬러 지정
			gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  "); Sleep(150);
		}
		if (file == 0) { //예외처리
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			gotoxy(0, 0);//좌표지정
			printf("ERROR");
		}
		else {
			fprintf(file, "%d", score);//점수를 파일에 저장
			fclose(file);//파일닫기
		}
	}
	getch();//키 중복 방지
}

void SecondS() {//점수창
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY);
	int y = -2;             
	
	gotoxy(30 ,y + 2); printf("+-- - - - - -+ ");
	gotoxy(30, y + 3); printf("|■        ■| ");
	gotoxy(30, y + 4); printf("|■        ■| ");
	gotoxy(30, y + 5); printf("|■        ■| ");
	gotoxy(30, y + 6); printf("|■level:%d ■|", score);
	gotoxy(30, y + 7); printf("|■        ■| ");
	gotoxy(30, y + 8); printf("|■        ■| ");
	gotoxy(30, y + 9); printf("|■■■■■■| ");
	gotoxy(30, y + 10); printf("+-- - - - - + ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(30, y + 11); printf(" YOUR SCORE :");
	gotoxy(30, y + 12); printf("        %6d", score*100);//점수 1당 100점
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy(30, y + 13); printf(" LAST SCORE :");
	gotoxy(30, y + 14); printf("        %6d", last_score*100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	gotoxy(30, y + 15); printf(" BEST SCORE :");
	gotoxy(30, y + 16); printf("        %6d", best_score*100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	gotoxy(30, y + 17); printf("  △   : Shift        SPACE : Hard Drop");
	gotoxy(30, y + 18); printf("◁  ▷ : Left / Right   P   : Pause");
	gotoxy(30, y + 19); printf("  ▽   : Soft Drop     ESC  : Quit");
	
	

	
}


void pause(void) { //게임 일시정지 함수 
	

	int x = 5;//좌표 지정
	int y = 5;

	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
		gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
		gotoxy(x, y + 1); printf("▤                              ▤");
		gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
		gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
		gotoxy(x, y + 6); printf("▤                              ▤");
		gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	
	getch(); //키입력시까지 대기 

	system("cls");  //화면지우기


	
}  

void Init() {//초기설정
	CONSOLE_CURSOR_INFO cursorInfo;//커서 설정 구조체
	cursorInfo.bVisible = 0;//커서 안보이게 1이면 보임
	cursorInfo.dwSize = 1;//사이즈
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//커서 핸들 &구조체 적용
	srand(time(NULL));//난수발생 시드값 고정 x
}
void gotoxy(int x, int y) {//커서위치 좌표 조정
	/*COORD pos;
	pos.X = x;
	pos.Y = y;*/
	COORD pos = { x, y };//F12에 의하면 COORD short x,y를 나타내고
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//커서의 위치를 나타내는 핸들 에게 위치를 지정함으로써
	//커서의 위치가 좌표의 위치에 따라 변하게 됨!
}
void CreateRandomForm() {//새로운 블럭 생성 

	blockForm = rand() % 7;//7가지 형태의 블록을 난수로 받아옴
	
	switch (blockForm) {//어떤 블록이냐에 따라 색깔을 다르게함
	case 0:
		color = RED;
		break;
	case 1:
		color = GREY;
		break;
	case 2:
		color = BLUE;
		break;
	case 3:
		color = GREEN;
		break;
	case 4:
		color = YELLOW;
		break;
	case 5:
		color = PUPLE;
		break;
	case 6:
		color = WHITE;
		break;

	}
}
bool CheckCrash(int x, int y) {//블록의 충동 검사
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2];//현재 벽상태에서 x좌표는 2배가 되야 1칸이 이기에 x/2이렇게 써야됨
				if (t == 1 || t == 2) { // 벽일 때, 블럭일 때
					return true;
				}
			}
		}
	}
	return false;
}
void DropBlock() {
	
	endT = clock();//끝시간 측정 
	if ((float)(endT - startDropT) >= speed) {//clock함수의 반환값은 프로세스가 현재실행까지 걸린 clock수이다.
		//실행 이때 speed는 clock수를 나타내므로 clock을 초로바꾸어 계산하면 speed는 800이며 0.8초로 계산된다 즉 clock간격이 적을수록 더많이 실행되므로
		//속도로 생각할수 있는것이다.
		if (CheckCrash(x, y + 1) == true) return;//충돌체크 충돌하면 함수 종료 바닥때문에 y값을+1함
		y++;//y값 증가 블록의 좌표를 이동
		startDropT = clock();//다시 시작점 생성 
		startGroundT = clock();//바닥에 닿는걸 체크할 시점 생성
		system("cls");//화면 클리어 why 움직일때 마다 보여주여야 하기 때문에 
	}
}
void BlockToGround() {//바닥에 닿은지 확인 하는 함수
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 100) {
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			CreateRandomForm();//새로운 블록 생성
			x = 8;//블록이 생성되는 좌표
			y = 0;
			
			if (score == 1) {
				speed = 600;
		  }
			else if(score==2)
				speed = 500;
			else if (score == 3)
				speed = 400;
			else if (score == 4)
				speed = 300;
			else if (score >= 5)
				speed = 200;
			else
				speed = 800;
			
			
		// 스페이스바로 하이드랍시 블럭은 아래에 박히니 속도를 다시 조정해서 원래대로 만듬
		}
	}
}
void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값 i는 높이 세로길이가 15인 
		int l = 0;//줄 체크 변수
		for (int j = 1; j < 11; j++) { //가로길이가 12이므로 대신 벽이 2개 있으므로 10번 반복
			if (space[i][j] == 2) {//블록중에 □이면 
				l++;// □갯수 체크 
			}
		}
		if (l >= 10) { // 블록이 다 차있다면 블록이 10개로 다 채워진다면
			PlaySound(TEXT("clear.wav"), NULL, SND_ASYNC);//clear.wqv 일반재생 모드로 실행
			++score;//점수 추가
			
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
			        if (i - j - 1 >= 0) {//ex 두줄중 밑에 줄이 다채웠다 치면 내려가게 복사하는
		               space[i - j][x] = space[i - j - 1][x];//x값은 그대로 y값만 한층 내려감
					}
					else    // 천장이면 0저장 
						space[i - j][x] = 0;
					
				}
			}
		}
	}
}

void DrawMap() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			if (space[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("▩");
			}
			else if (space[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("□");
			}
			}
	}

	
}
void DrawBlock() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				printf("■");
			}
		}
	}
	
}
void InputKey() {
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case 72: //up
			if ((CheckCrash(x - 2, y) != true) && (CheckCrash(x + 2, y) != true)) {
				blockRotation++;

				if (blockRotation >= 4) blockRotation = 0;
				startGroundT = clock();
			}
			break;
		//이부분에서 if (CheckCrash(x - 2, y) == false) 바닥일때 체크하는것과  벽일때 체크하는 것이 필요
		case 75: // left
			
				if (CheckCrash(x - 2, y) == false) {
					x -= 2;
					startGroundT = clock();
				}
			
			break;
		case 77: // right
			
				if (CheckCrash(x + 2, y) == false) {
					x += 2;
					startGroundT = clock();
				}

			break;
		case 80: // down
			if (CheckCrash(x, y + 1) == false)
				y++;
			break;
		case 32: // space
			PlaySound(TEXT("drop.wav"), NULL, SND_ASYNC);
			speed = 1;
			startGroundT = clock();
			break;

		case p:
			pause();
			break;
		case ESC:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			system("cls");
			exit(0);
			break;
		}
		
		system("cls");
	}
}

