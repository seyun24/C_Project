#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <stdbool.h>// bool Ÿ�� ��밡���ϰ� ��
#pragma comment(lib, "winmm.lib")//�뷡 ����� �����ִ� ��ó����
#pragma warning(disable:4996)//_�� �ȴ޾Ƶ��� file �Է� �Ҷ� ������ �־���

#define RED 4
#define BLUE 1
#define YELLOW 6
#define GREEN 2
#define PUPLE 5
#define WHITE 7
#define GREY 8
#define p 112 //�Ͻ����� 

#define ESC 27 //�ܼ� ����


clock_t startDropT, endT, startGroundT;//long���� �ٸ��̸��� typedef�Ѱ����� time.h ��������� �־�� ��밡�� 
//����� �̵��� �׼���,����� ���� ��������� �ð�, 
int x = 8, y = 0;//�⺻ ��ǥ
//RECT blockSize;
int blockForm;//������� 7����
int blockRotation = 0;//��� ������ 4���� ����
int key;//keybord ???
int speed = 800;//�� �������� �ӵ� ���� ���� clock�Լ������� 1000Ŭ���� 1�ʶ� �����ϱ⿡ 0.8�� ??? 

int block[7][4][4][4] = {//7���� ����, 4���� ȸ��,���� ����� �׸� 2�����迭
	{ // T��� ��
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
	{    // ���� ��
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
	{   // ���� �� �ݴ�
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
	{   // 1���� ��
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
	{   // L���� ��
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
	{   // L���� �� �ݴ�
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
	{   // �׸� ��
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


int space[16][12] = { //������ ����� ����ȭ���� ��Ÿ���� 2�����迭 0�� ��ȭ�� 1�� ���� ��Ÿ��
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

int CopyMap[16][12] = {  //������ �����ϰ� �ٽ� �����Ҷ� space�� �ִ� ���� �ʱⰪ�� �ٲپ� ������ �ʱ�ȭ��Ű�� �뵵
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



void Init();//�ʱ� ����
void gotoxy(int x, int y);//Ŀ���� �����̴� �Լ�
void CreateRandomForm();//���¿� �÷��� �ٸ� ��� ȣ��ɶ����� ����
bool CheckCrash(int x, int y);//�浹 �������ִ� �Լ�(�̿�)
void DropBlock();//����� �ϰ��ӵ� ���� �Լ�
void BlockToGround();//����� �ٴڰ� �������� ó���Ǵ� ȣ�����
void RemoveLine();//���� ä�������� �ش����� ����� ����� �̵���Ű�� �Լ�
void DrawMap();//space�� �ݿ��Ͽ� �������� �׸�
void DrawBlock();//block�迭�� �����Ͽ� �ش� block�� ����ϴ� �Լ�
void InputKey();//keybord�� �Է��� �޾ƿ��� �ش� Ű�� �´� ������� 
bool GameOver();//���ӿ��� üũ
void ResetGame();//�� ����
void SecondS();//����ȭ�� �� ȭ��
void game_over();//���ӿ��� ��ũ��
void reset_score();//���� �ʱ�ȭ �� ����



int color;
int score = 0;


int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 
int main() {
    one://goto���� ���̺� ������ one���� �̵�
	
	Init();//�ʱ����
	startDropT = clock();//Ŭ�� �Լ� ��� 1000Ŭ���� 1�� ������ üũ
	
	color = 1;
	reset_score();//���� ���� �ʱ�ȭ �� ����
	while (_kbhit() == 0) {//������ ��� �ٲٰ� ����� Ʋ�����ؼ� �ݺ��� ���! 
		PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);//start.wav�����ؼ� �Ϲ���� ���� ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color % 16);	
		gotoxy(0, 0); printf("��������������������������������"); Sleep(100); //window.h���� ������ os �����ϴ� api�Լ� 1000 == 1��
		gotoxy(0, 1); printf("���ǢǢǡ��ǢǢǡ��ǢǢǡ��ǢǢǡ���ǡ���Ǣǡ��"); Sleep(100); //���帶�� 0.1�ʾ� ������ �������ν� ����ó�� ����
		gotoxy(0, 2); printf("����ǡ���ǡ�����ǡ���ǡ��ǡ��ǡ��ǡ����"); Sleep(100); //���Ϲ� ������ ����ؼ� ����Ʈ �Ǳ⶧���� ��ǥ�� �������Ѿߵ� 
		gotoxy(0, 3); printf("����ǡ���ǢǢǡ���ǡ���ǢǢǡ���ǡ���ǡ���"); Sleep(100); //�׷��� gotoxy�� ����
		gotoxy(0, 4); printf("����ǡ���ǡ�����ǡ���ǡ�ǡ���ǡ����ǡ��"); Sleep(100); 
		gotoxy(0, 5); printf("����ǡ���ǢǢǡ���ǡ���ǡ��ǡ��ǡ��Ǣǡ���"); Sleep(100); 
		gotoxy(0, 6); printf("��������������������������������"); Sleep(100); 
		gotoxy(0, 7); printf("��������������������������������"); Sleep(100); 
		gotoxy(0, 8); printf("                                   project by 202104016 �ڼ���"); Sleep(100); 
		gotoxy(9, 11);  printf("      press any key to start");
		
		for (int z = 0; z < 50; z++) {//����ȭ�� ����� ȭ��������Ű�� �� 1.5��
			Sleep(30); //0.03�ʾ� 
			if (_kbhit()) break;//����� ���� �ִ� ������ �����ð��� ��޸��� �Ѿ�� ������ ���ڿ��������� �������� �������� �Ѿ�� ����!
		}
		color++;
		if (color % 16 == 0)//���� ����
			color++;
		
	}
	getch();//���� ���۸� �������ν� �ƹ�Ű�� �������� ����ȭ�鿡 ������ �����ʰ� ��
	CreateRandomForm();//����� ó�� ��� ����
	while (GameOver()) {//���ӿ��� ���θ� üũ�Ͽ� ���ӿ����Ǹ� �ݺ��� Ż��!
		//���ѹݺ��� �ؾ� ȭ���� �ݿ��Ǳ� ������ �ݺ����!
		DrawMap();//�⺻���� ȭ���� �׸���
		DrawBlock();//������ ����� �׸���
		DropBlock();//�������� ����� �������� ����
		BlockToGround();//����� ���� ������� ó��
		RemoveLine();//������ ä������ ������ �ٹٲ�
		InputKey();//Ű������ �Է��� �ް� �ش繮�� ����
		SecondS();//����ȭ�� ���� ����� �ִ� ����â
		
	}
	
	system("cls");//���� ȭ���� ������


	game_over();//���ӿ��� ��ũ�� ���
		

	system("cls");//���� ���� ȭ�� ������
	 
	ResetGame();//���� �ʱ�ȭ
	goto one;//ó������ ���̺� >one
	return 0;
}
bool GameOver() {//2�����迭 space�� ù��° �࿡ 2��� ���� �ϳ��� ������ ��������
	for (int j = 0; j < 12; j++) {
		if (space[0][j] == 2) {//0��°�� üũ�ϸ�� 
			return false;
		}
		else true;
	}
}
void ResetGame() {//��µ̴� ����ȭ���� �������·� �ʱ�ȭ(����ȭ�� �ʱ�ȭ)
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			space[i][j] = CopyMap[i][j]; //�ʱ��� �迭�� ���Ҹ� �Ȱ��� ������ CopyMap�� space�� ����
		}
	}
}
void reset_score(void) {//���� �ʱ�ȭ �� ����
	score = 0;//score�� 0����
	
	FILE* file = fopen("score.txt", "rt"); // score.dat������ ���� 
	if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
	else {
		fscanf(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
		fclose(file); //���� ���� 
	}
}
void game_over()//game over ��ũ��
{
	
	PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);//gameover.wav �Ϲ�������� ���
	if (score > best_score) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	}
	else 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
	gotoxy(x, y + 1); printf("��                              ��");
	gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
	gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
	gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
	gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score*100);//���� 1�� 100��
	gotoxy(x, y + 6); printf("��                              ��");
	gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
	gotoxy(x, y + 8); printf("��                              ��");
	gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	last_score = score; //�ֱ������� ���� 
	if (score > best_score) { //�ְ��� ���Ž� 
		
		FILE* file = fopen("score.txt", "wt"); //score.txt�� ���� ����                
		PlaySound(TEXT("clip.wav"), NULL, SND_ASYNC);//clip.wav �Ϲݸ��� ���
		while (kbhit() == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);//�ʷϻ� �÷� ����
			gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  "); Sleep(150);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//�Ͼ�� �÷� ����
			gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  "); Sleep(150);
		}
		if (file == 0) { //����ó��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			gotoxy(0, 0);//��ǥ����
			printf("ERROR");
		}
		else {
			fprintf(file, "%d", score);//������ ���Ͽ� ����
			fclose(file);//���ϴݱ�
		}
	}
	getch();//Ű �ߺ� ����
}

void SecondS() {//����â
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY);
	int y = -2;             
	
	gotoxy(30 ,y + 2); printf("+-- - - - - -+ ");
	gotoxy(30, y + 3); printf("|��        ��| ");
	gotoxy(30, y + 4); printf("|��        ��| ");
	gotoxy(30, y + 5); printf("|��        ��| ");
	gotoxy(30, y + 6); printf("|��level:%d ��|", score);
	gotoxy(30, y + 7); printf("|��        ��| ");
	gotoxy(30, y + 8); printf("|��        ��| ");
	gotoxy(30, y + 9); printf("|�������| ");
	gotoxy(30, y + 10); printf("+-- - - - - + ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(30, y + 11); printf(" YOUR SCORE :");
	gotoxy(30, y + 12); printf("        %6d", score*100);//���� 1�� 100��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy(30, y + 13); printf(" LAST SCORE :");
	gotoxy(30, y + 14); printf("        %6d", last_score*100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	gotoxy(30, y + 15); printf(" BEST SCORE :");
	gotoxy(30, y + 16); printf("        %6d", best_score*100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	gotoxy(30, y + 17); printf("  ��   : Shift        SPACE : Hard Drop");
	gotoxy(30, y + 18); printf("��  �� : Left / Right   P   : Pause");
	gotoxy(30, y + 19); printf("  ��   : Soft Drop     ESC  : Quit");
	
	

	
}


void pause(void) { //���� �Ͻ����� �Լ� 
	

	int x = 5;//��ǥ ����
	int y = 5;

	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
		gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		gotoxy(x, y + 1); printf("��                              ��");
		gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
		gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
		gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
		gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
		gotoxy(x, y + 6); printf("��                              ��");
		gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	
	getch(); //Ű�Է½ñ��� ��� 

	system("cls");  //ȭ�������


	
}  

void Init() {//�ʱ⼳��
	CONSOLE_CURSOR_INFO cursorInfo;//Ŀ�� ���� ����ü
	cursorInfo.bVisible = 0;//Ŀ�� �Ⱥ��̰� 1�̸� ����
	cursorInfo.dwSize = 1;//������
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//Ŀ�� �ڵ� &����ü ����
	srand(time(NULL));//�����߻� �õ尪 ���� x
}
void gotoxy(int x, int y) {//Ŀ����ġ ��ǥ ����
	/*COORD pos;
	pos.X = x;
	pos.Y = y;*/
	COORD pos = { x, y };//F12�� ���ϸ� COORD short x,y�� ��Ÿ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//Ŀ���� ��ġ�� ��Ÿ���� �ڵ� ���� ��ġ�� ���������ν�
	//Ŀ���� ��ġ�� ��ǥ�� ��ġ�� ���� ���ϰ� ��!
}
void CreateRandomForm() {//���ο� �� ���� 

	blockForm = rand() % 7;//7���� ������ ����� ������ �޾ƿ�
	
	switch (blockForm) {//� ����̳Ŀ� ���� ������ �ٸ�����
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
bool CheckCrash(int x, int y) {//����� �浿 �˻�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2];//���� �����¿��� x��ǥ�� 2�谡 �Ǿ� 1ĭ�� �̱⿡ x/2�̷��� ��ߵ�
				if (t == 1 || t == 2) { // ���� ��, ���� ��
					return true;
				}
			}
		}
	}
	return false;
}
void DropBlock() {
	
	endT = clock();//���ð� ���� 
	if ((float)(endT - startDropT) >= speed) {//clock�Լ��� ��ȯ���� ���μ����� ���������� �ɸ� clock���̴�.
		//���� �̶� speed�� clock���� ��Ÿ���Ƿ� clock�� �ʷιٲپ� ����ϸ� speed�� 800�̸� 0.8�ʷ� ���ȴ� �� clock������ �������� ������ ����ǹǷ�
		//�ӵ��� �����Ҽ� �ִ°��̴�.
		if (CheckCrash(x, y + 1) == true) return;//�浹üũ �浹�ϸ� �Լ� ���� �ٴڶ����� y����+1��
		y++;//y�� ���� ����� ��ǥ�� �̵�
		startDropT = clock();//�ٽ� ������ ���� 
		startGroundT = clock();//�ٴڿ� ��°� üũ�� ���� ����
		system("cls");//ȭ�� Ŭ���� why �����϶� ���� �����ֿ��� �ϱ� ������ 
	}
}
void BlockToGround() {//�ٴڿ� ������ Ȯ�� �ϴ� �Լ�
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 100) {
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			CreateRandomForm();//���ο� ��� ����
			x = 8;//����� �����Ǵ� ��ǥ
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
			
			
		// �����̽��ٷ� ���̵���� ���� �Ʒ��� ������ �ӵ��� �ٽ� �����ؼ� ������� ����
		}
	}
}
void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // ������ ������ �� i�� ���� ���α��̰� 15�� 
		int l = 0;//�� üũ ����
		for (int j = 1; j < 11; j++) { //���α��̰� 12�̹Ƿ� ��� ���� 2�� �����Ƿ� 10�� �ݺ�
			if (space[i][j] == 2) {//����߿� ���̸� 
				l++;// �హ�� üũ 
			}
		}
		if (l >= 10) { // ����� �� ���ִٸ� ����� 10���� �� ä�����ٸ�
			PlaySound(TEXT("clear.wav"), NULL, SND_ASYNC);//clear.wqv �Ϲ���� ���� ����
			++score;//���� �߰�
			
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
			        if (i - j - 1 >= 0) {//ex ������ �ؿ� ���� ��ä���� ġ�� �������� �����ϴ�
		               space[i - j][x] = space[i - j - 1][x];//x���� �״�� y���� ���� ������
					}
					else    // õ���̸� 0���� 
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
				printf("��");
			}
			else if (space[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("��");
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
				printf("��");
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
		//�̺κп��� if (CheckCrash(x - 2, y) == false) �ٴ��϶� üũ�ϴ°Ͱ�  ���϶� üũ�ϴ� ���� �ʿ�
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

