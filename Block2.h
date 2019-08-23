#pragma once
#include <time.h>
#include<conio.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include<MMStream.h>//����������Ҫ��ͷ�ļ�
#pragma comment(lib,"winmm.lib")//����winmm���ļ�

using namespace std;
constexpr int BLOCK_HEIGHT = 5;
constexpr int BLOCK_WIDTH = 5;
constexpr int BLOCK_DIR = 4;
constexpr int BRICK_SIZE = 20;
constexpr int BRICK_COUNT = 5;
constexpr int START_X = 130;
constexpr int START_Y = 30;
constexpr int BLOCK_START_X = 27;
constexpr int BLOCK_START_Y = 27;
constexpr int PANE_RIGHT = 336;
constexpr int KEY_UP=	72;
constexpr int KEY_RIGHT	=77;
constexpr int KEY_DOWN=	80;
constexpr int KEY_LEFT	=75;
constexpr int KEY_SPACE=	32;
constexpr int INIT_SPEED = 500;
constexpr int G_VISIT_Y = 30;
constexpr int G_VISIT_X = 15;
constexpr int MIN_SPEED = 50;
typedef enum {
	BLOCK_UP,//0
	BLOCK_RIGHT,//1
	BLOCK_DOWN,//2
	BLOCK_LEFT//3
} block_dir_t;//ö����

typedef enum {
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
} move_dir_t;

int NextIndex = -1;  //��һ�����������
int BlockIndex = -1; //��ǰ���������


int blockArr[BLOCK_DIR * 5][BLOCK_HEIGHT][BLOCK_WIDTH] = { { 0,0,0,0,0,  0,0,1,0,0,  0,0,1,0,0,  0,0,1,0,0,  0,0,0,0,0 },// | �η���
								 { 0,0,0,0,0,  0,0,0,0,0,  0,1,1,1,0,  0,0,0,0,0,  0,0,0,0,0 },
								 { 0,0,0,0,0,  0,0,1,0,0,  0,0,1,0,0,  0,0,1,0,0,  0,0,0,0,0 },
								 { 0,0,0,0,0,  0,0,0,0,0,  0,1,1,1,0,  0,0,0,0,0,  0,0,0,0,0 },
									 { 0,0,0,0,0,	0,0,1,0,0,	0,0,1,0,0,	0,0,1,1,0,	0,0,0,0,0 },// L �η���
							   { 0,0,0,0,0,	0,0,0,0,0,	0,1,1,1,0,	0,1,0,0,0,	0,0,0,0,0 },
							   { 0,0,0,0,0,	0,1,1,0,0,	0,0,1,0,0,	0,0,1,0,0,	0,0,0,0,0 },
							   { 0,0,0,0,0,	0,0,0,1,0,	0,1,1,1,0,	0,0,0,0,0,	0,0,0,0,0 },
	// �� �η���
		{ 0,0,0,0,0,	0,1,1,0,0,	0,1,1,0,0,	0,0,0,0,0,	0,0,0,0,0 },
		{ 0,0,0,0,0,	0,1,1,0,0,	0,1,1,0,0,	0,0,0,0,0,	0,0,0,0,0 },
		{ 0,0,0,0,0,	0,1,1,0,0,	0,1,1,0,0,	0,0,0,0,0,	0,0,0,0,0 },
		{ 0,0,0,0,0,	0,1,1,0,0,	0,1,1,0,0,	0,0,0,0,0,	0,0,0,0,0 },
	// T �η���
{ 0,0,0,0,0,	0,1,1,1,0,	0,0,1,0,0,	0,0,0,0,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,0,0,1,0,	0,0,1,1,0,	0,0,0,1,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,0,1,0,0,	0,1,1,1,0,	0,0,0,0,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,1,0,0,0,	0,1,1,0,0,	0,1,0,0,0,	0,0,0,0,0 },
// Z �η���
{ 0,0,0,0,0,	0,1,1,0,0,	0,0,1,1,0,	0,0,0,0,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,0,1,0,0,	0,1,1,0,0,	0,1,0,0,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,1,1,0,0,	0,0,1,1,0,	0,0,0,0,0,	0,0,0,0,0 },
{ 0,0,0,0,0,	0,0,1,0,0,	0,1,1,0,0,	0,1,0,0,0,	0,0,0,0,0 }
};
int color[BRICK_COUNT] = { YELLOW,GREEN,LIGHTMAGENTA,RED,CYAN };
int g_visit[G_VISIT_Y][G_VISIT_X] = {};//��Ϸ�����淽����,����Ԫ��ȫ����ʼ��Ϊ0
int fixedColor[G_VISIT_Y][G_VISIT_X] = {};
//int clearIndex;

void welcome() {
	initgraph(600, 700);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("���º췽��"));
	settextstyle(30, 0, _T("����")); setcolor(WHITE);
	outtextxy(150, 175, _T("����˹����"));
	outtextxy(150, 225, _T("��̴�װB��ʼ(*^_^*)"));
	Sleep(2000);
}
short score = 0; 
short rank1 = 0;
void initgameScene() {
	cleardevice();//�����ӭ����
	setcolor(WHITE);
	rectangle(BLOCK_START_X, BLOCK_START_Y, PANE_RIGHT, 635);//����
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 470, 150);
	outtextxy(380, 170, _T("��һ��"));
	setcolor(RED); outtextxy(405, 280, _T("����:"));
	//����ת���ַ��� 
	TCHAR str[16];
	swprintf_s(str, _T("%d"), score);
	outtextxy(415, 310, str);
	outtextxy(405, 375, _T("�ȼ���"));
	swprintf_s(str, _T("%d"), rank1);
	outtextxy(415, 410, str);
	for (short a = 0; a <= 5; a++) {
		short y = a * 30;
		switch (a)
		{
		case 0:outtextxy(390, 475 + y, _T("����˵����")); break;
		case 1:outtextxy(390, 475 + y, _T("����ת")); break;
		case 2:outtextxy(390, 475 + y, _T("���½�")); break;
		case 3:outtextxy(390, 475 + y, _T("������")); break;
		case 4:outtextxy(390, 475 + y, _T("������")); break;
		case 5:outtextxy(390, 475 + y, _T("�ո���ͣ")); break;
		default:
			break;
		}
	}
}bool borderCheck; short dir = BLOCK_UP;
inline void drawBlock(short x, short y, short randomIndex) {
	 borderCheck=0;
	settextstyle(23, 0, _T("(΢���ź�)")); setcolor(color[randomIndex]);
	for (short j = 0; j < 5; j++) {
	
		for (short i = 0; i < 5; i++) {
			
			if (blockArr[randomIndex * 4+dir][j][i] == 1) {//��x�Ὺʼɨ��ɨ������һ����1�ľ����,*4����ÿ�ַ���ĵ�һ������			
				
				outtextxy(x + i * BRICK_SIZE, y + j * BRICK_SIZE, _T("��"));//����Ҫ��΢�ȷ����
			}
		}
	}
}
void clearBlock(short x=371, short y=51) {//371, 51Ĭ�ϲ���
	setcolor(BLACK);
	settextstyle(19, 0, _T("(΢���ź�)"));
	for (short j = 0; j < 5; j++) {

		for (short i = 0; i < 5; i++) {

			outtextxy(x + i * BRICK_SIZE, y + j * BRICK_SIZE, _T("��"));//370, 50, 520, 200
		}
	}
}
unsigned short speed;
inline void clearBlock(short x, short y, short dir) {
	if (borderCheck) {
		return;
	}
	setcolor(BLACK);
	settextstyle(20, 0, _T("(΢���ź�)"));
	for (short j = 0; j < 5; j++) {
		for (short i = 0; i < 5; i++) {
			if (blockArr[BlockIndex * 4 + dir][j][i] == 1) {//��x�Ὺʼɨ��ɨ������һ����1�ľ����,*4����ÿ�ַ���ĵ�һ������
					outtextxy(x + i * BRICK_SIZE, y + j * BRICK_SIZE, _T("��"));//����Ҫ��΢�ȷ����			
			}
		}
	}
}
short randomIndex = NextIndex;
void nextBlock() {
	settextstyle(23, 0, _T("(΢���ź�)"));
	//BlockIndex = NextIndex;
	if (randomIndex != -1) {
		clearBlock();
	}
	srand((unsigned)time(NULL));//�������(ʱ��)����
	randomIndex = rand() % BRICK_COUNT ;//ȡ�࣬��֤������0-4
	NextIndex = randomIndex;//��һ��������
	drawBlock(370, 50, NextIndex);
}
void downBlock();

void  newBlock() {
	BlockIndex = NextIndex;
	drawBlock(START_X, START_Y, BlockIndex);
	Sleep(500);
	nextBlock();
	downBlock();
}
int disTab[size(g_visit)] = {};//�з������˱��
short minX= BLOCK_START_X + 3;
short minY= BLOCK_START_Y + 3;
void fixedBlock(short x, short y, short dir) {//����̶����������
	short x2 = (x - minX) / BRICK_SIZE;
	short y2 = (y -minY ) / BRICK_SIZE;
	
	for (short j = 0; j <5; j++) {

		for (short i = 0; i <5; i++) {

			if (blockArr[BlockIndex * 4 + dir][j][i] == 1) {
				g_visit[y2 + j][x2 + i] = 1;//��������ƹ̶���
				fixedColor[y2 + j][x2 + i] = color[BlockIndex];
				disTab[y2 + j] = 1;
			}
		}
	}newBlock();
}

bool touchCheck(short x, short y, short dir,move_dir_t movDir) {//�������������ҵķ���Ƚ�
	short a; bool moved = 0;
	short x2 = (x - minX) / BRICK_SIZE;
	short y2 = (y - minY) / BRICK_SIZE;
	if (movDir == MOVE_DOWN) {
		for (short i = 0; i < 5; i++) {
			for (short j = 0; j < 5; j++) {
				if (blockArr[BlockIndex * 4 + dir][j][i] == 1 &&
					((y2 + j) >= G_VISIT_Y-1 || g_visit[y2 + j+1][x2 + i] == 1)) {//
					mciSendString(_T("play hinderSound.mp3 "), 0, 0, 0);//
					moved = 1;
				}
			}
		}
	}
	else if (movDir == MOVE_LEFT) {
		for (short j = 0; j < 5; j++) {
			for (short i = 0; i < 5; i++) {
				a = g_visit[y2 + j][x2 + i-1];//�����һλ��0
				if (blockArr[BlockIndex * 4 + dir][j][i] == 1 && (a == 1 || (x2 + i+1) == 0)) {//���������飬��߿�Ա�
					mciSendString(_T("play hinderSound.mp3 "), 0, 0, 0);//��������
					moved = 1;
				}
			}
		}
	}
	else  if(movDir == MOVE_RIGHT) {
				for (short j = 0; j < 5; j++) {
					for (short i = 0; i < 5; i++) {
						a = g_visit[y2 + j][x2 + i + 1];
						if (blockArr[BlockIndex * 4 + dir][j][i] == 1 && (a == 1 || (x2 + i)>=G_VISIT_X)) {
							mciSendString(_T("play hinderSound.mp3 "), 0, 0, 0);//��������
							moved = 1;
						}
					}

		}
	}	
	return moved;
}
bool rotatable(short x, short y, block_dir_t dir) {
	short id = BlockIndex * 4 + dir;
			
	short x2 = (x - minX) / BRICK_SIZE;
	short y2 = (y - minY) / BRICK_SIZE;

			if (touchCheck(x, y, dir,MOVE_DOWN )) {
				return 0;
			}
			for (short i = 0; i < 5; i++) {
				for (short j = 0; j < 5; j++) {
					if (blockArr[id][j][i] == 1 &&
						(x2 + i < 0 || x2 + i >= G_VISIT_X || g_visit[y2 + j][x2 + i] == 1)) {//���ұȽ�
						return 0;
					}
				}
			}

			return 1;
		}

void downBlock();


bool overCheck(short x, short y, short dir) {//����������˾͹���
	int a; bool over = 0;
	for (short j = 0; j < 5; j++) {
		for (short i = 0; i < 5; i++) {
			a = g_visit[2][(x - BLOCK_START_X) / BRICK_SIZE + i];
			if (blockArr[BlockIndex * 4 + dir][j][i] == 1 && a == 1) {				
				return 1;
			}
		}
	}
	return over;	
}

void down(short j);
void disappear() {//����
	
	short count = 0;   int j ;   int i;
	for ( j = G_VISIT_Y-1; j >=0 ;j--) {
		if (count == G_VISIT_X) {//�ж���û��
			down(j + 1);//���к��½�
			mciSendString(_T("play eliminate.mp3 "), 0, 0, 0);//��������
			//setcolor(BLACK);
			settextstyle(BRICK_SIZE+3, 0, _T("(΢���ź�)"));
			/*void settextstyle(int nHeight, int nWidth, LPCTSTR lpszFace, int nEscapement, 
			int nOrientation, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut); */										  										
			for (short c1 = 0; c1 < 2;c1++) {
				for (short c = 0; c < 2; c++) {
					outtextxy(415+c * BRICK_SIZE, 310+ c1 * BRICK_SIZE, _T("��"));//�����
					outtextxy(415 + c * BRICK_SIZE, 410 + c1 * BRICK_SIZE, _T("��"));//��ȼ�
				}
			}
			setcolor(LIGHTBLUE);
			//settextstyle(23, 0, _T("(΢���ź�)"), 0, 0, 50, 0, 0, 0);
			score += 10; rank1 = score / 100;
			TCHAR p_str[8]; swprintf_s(p_str, _T("%d"), score);//���·���
			 outtextxy(415, 310, p_str);
			 swprintf_s(p_str, _T("%d"), rank1);//���·���
			 outtextxy(415, 410, p_str);
			break;
		}
		count = 0;
		for ( i = size(g_visit[1])-1; i >= 0 && g_visit[j][i]; i--) {			
				count ++;			
		}
	}	
}
inline void wait(short interval) {//�½��ٶȣ�������ʱ��Ӧ
	int count = interval / 10;
	for (short i = 0; i < count; i++) {
		Sleep(10);
		if (_kbhit()) {
			return;
		}
	}
}
void down(short _j) {//���к���½�
	for (unsigned short j = _j; j >0; j--) {
		if (disTab[j] == 0) {
			break;
		}	
		for (unsigned short i = 0; i < size(g_visit[1]); i++) {
			if (g_visit[j-1][i]) {
				setcolor(fixedColor[j-1][i]);
				settextstyle(BRICK_SIZE+3, 0, _T("(΢���ź�)"));				
					outtextxy(i * BRICK_SIZE + minX, j * BRICK_SIZE + minY, _T("��"));//30����ʼ����,����y��Ҫ�ȵ��¸�20
					g_visit[j][i] = g_visit[j - 1][i]; fixedColor[j][i] = fixedColor[j - 1][i];
			}
			else {
				setcolor(BLACK);
				settextstyle(BRICK_SIZE, 0, _T("(΢���ź�)"));
				//for (unsigned int c = 0; c < size(g_visit[1]); c++) {//������������һ��
					outtextxy(i * BRICK_SIZE + minX, (j)* BRICK_SIZE + minY, _T("��"));//30����ʼ����
					g_visit[j][i] = 0; //������������0���ٰ���һ�и�������
					fixedColor[j][i] = 0; 
				//}
			}			
		}
	}
	
}
void keyCheck(block_dir_t nextDir, short*down_x, short*down_y, short key,unsigned short* sp) {
	
	switch (key)
	{
	case KEY_SPACE://�ո�
		key = _getch();//��ͣ
		break;
	case KEY_UP://��
		nextDir = (block_dir_t)((dir + 1) % 4);
		if (rotatable(*down_x, *down_y + BRICK_SIZE, nextDir)) {
			dir = nextDir;
		}
		break;
	case KEY_RIGHT://��
		if (!touchCheck(*down_x + BRICK_SIZE, *down_y + BRICK_SIZE, dir, MOVE_RIGHT)) {

			*down_x += BRICK_SIZE;
		}break;
	case KEY_DOWN://��
		*sp = MIN_SPEED;
		break;
	case KEY_LEFT://��
		if (!touchCheck(*down_x - BRICK_SIZE, *down_y + BRICK_SIZE, dir, MOVE_LEFT)) {//�ж�����
			*down_x -= BRICK_SIZE;
		}
		break;

	}
}
void downBlock() 
{
	
	short down_x = START_X;  short down_y = START_Y;
	 unsigned short speed = INIT_SPEED;
	 unsigned short* sp = &speed;
	 disappear();
	 speed = INIT_SPEED - rank1 * 50;
	 if (speed<MIN_SPEED) {
		 speed = 100;
	 }
	 if (overCheck(down_x, down_y, dir)) {//��Ϸ����
		 settextstyle(30, 0, _T("����")); setcolor(WHITE);
		 outtextxy(80, 175, _T("�����GAMEOVER"));
		 system("pause");
		 exit(0);
		 return;
	 }block_dir_t nextDir=BLOCK_UP;
	 while (1) {		 
		 clearBlock(down_x, down_y, dir);//�����ǰ����
		 if (_kbhit()) {//�������
			 short key = _getch();//�������µļ�
			 keyCheck(nextDir,&down_x,&down_y,key,sp);
		 }		 
		 down_y += BRICK_SIZE;//�����»��Ʒ���		
		 drawBlock(down_x, down_y, BlockIndex);
		 if (touchCheck(down_x, down_y, dir, MOVE_DOWN)) {//�̶�
			 fixedBlock(down_x, down_y,  dir);
			 break;
		 }
	 wait(speed); 

	}
}
 

							   



 