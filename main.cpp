//farkle main
#include "farkle.h"
#include "Genetic.h"
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));	// sets global random seed based on system time, VERY IMPORTANT, may move to Farkle class
	Farkle Game(0,2,1);
	Game.playHumans();
	
	//Game.storeAI("test2.txt", 0);
	//above lines are success!
	Genetic g = Genetic(10);
	while(!g.converge()){
		g.step();
	}
}