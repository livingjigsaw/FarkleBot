//farkle main
#include "farkle.h"
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));	// sets global random seed based on system time, VERY IMPORTANT, may move to Farkle class
	Farkle Game(1,1,1);
	Game.readAI("testin.txt", 0);
	//Game.storeAI("test2.txt", 0);
	//above lines are success!

}