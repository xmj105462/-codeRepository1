#include <iostream>

#include<graphics.h>

#include "Block.h"

using namespace std;


int main() {
	
	welcome();
	initgameScene();
	nextBlock();
	Sleep(1000);
	while (1) {
		newBlock();
	}
	

	
	closegraph();
	system("pause");

	return 0;
}
 
