#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include <time.h>
//#include <ctype.h>
#include "Block.h"

using namespace std;


int main() {
	
	welcome();
	initgameScene();
	nextBlock();
	Sleep(1000);
	newBlock();
	

	
	closegraph();
	system("pause");

	return 0;
}
 
