//farkle main
#include "farkle.h"
#include <iostream>

using namespace std;

int main(){
	PlayerFactory factory;
	factory.set_players(0,0,0,1000); // creates players
	Farkle Game;
	ShouseAlgorithm genetic(1000); // prepares the genetic algorithm
	factory.makePlayers(Game, genetic); 
	//cout << "debug Main\n";
	for(int i=0;i<1000;i++){
		Game.trainBots(20);//this should play several rounds and average scores for better results
		genetic.Breed();
		Game.reset();
	}
	//cout << "i have bots!" << endl;
	
	
	//Game.storeAI("test2.txt", 0);
}