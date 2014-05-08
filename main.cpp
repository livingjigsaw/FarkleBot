//farkle main
#include "farkle.h"
#include <iostream>

using namespace std;

int main(){
	PlayerFactory factory;
	factory.set_players(2,0,0,0);
	Farkle Game;
	ShouseAlgorithm genetic(1);
	factory.makePlayers(Game, genetic);
	cout << "debug Main\n";
	Game.playHumans();
	
	//Game.storeAI("test2.txt", 0);


}