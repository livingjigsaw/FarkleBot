//farkle main
#include "farkle.h"
#include "Genetic.h"
#include <iostream>

using namespace std;

int main(){
	PlayerFactory factory;
	factory.set_players(2,0,0,0);
	Farkle Game;
	factory.makePlayers(Game);
	cout << "debug Main\n";
	Game.playHumans();
	
	//Game.storeAI("test2.txt", 0);
	//above lines are success!
	Genetic g = Genetic(10);
	while(!g.converge()){
		g.step();
	}
}