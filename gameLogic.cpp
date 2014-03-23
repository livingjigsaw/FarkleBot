//this defines at least the scoring function by the Farkle class, meant to keep 
//the many, many conditionals out of the main h file
#include "farkle.h"
using namespace std;

Farkle::Farkle(int inBots, int inHumans, int inNumRounds){	
	numBots = inBots;
	numHumans = inHumans;
	numRounds = inNumRounds;
	numPlayers = numHumans+numBots;
	Dice = new Die[6];
	Players = new Player*[numPlayers];
	for(int i=0;i<numHumans;i++){
		Players[i] = new Human();
	}
	for(int i=numHumans;i<numPlayers;i++){
		Players[i] = new FarkleBot();
	}
	activePlayer=0; activeTurnScore = 0;
}	

Farkle::~Farkle(){
	for(int i=0;i<numPlayers;i++){
		delete Players[i];
	}
	delete [] Players;
	delete [] Dice;
}

bool Farkle::readAI(string filename, int botID){
	fstream in;
	in.open(filename.c_str(), ios::in);
	if(in.fail())
		return 0; 
	double temp = 0;
	in >> temp;
	Players[numHumans+botID]->set_param(0, temp);
	in >> temp;
	Players[numHumans+botID]->set_param(1, temp);
	in >> temp;
	Players[numHumans+botID]->set_param(2, temp);
	in >> temp;
	Players[numHumans+botID]->set_param(3, temp);

	return 1;
}

bool Farkle::storeAI(string filename, int botID){
	fstream out;
	out.open(filename.c_str(), ios::out);
	if(out.fail())
		return 0; 
	out << Players[numHumans+botID]->get_param(0) << endl;
	out << Players[numHumans+botID]->get_param(1) << endl;
	out << Players[numHumans+botID]->get_param(2) << endl;
	out << Players[numHumans+botID]->get_param(3) << endl;
	return 1;
}

bool Farkle::saveResults(string filename){
	fstream out;
	out.open(filename.c_str(), ios::out);
	if(out.fail())
		return 0; 
	for(int i=0; i<numHumans;i++){
		out << "PlayerID= " << i << endl;
		out << "Score= " << Players[i]->get_score() << endl;
		out << "Turns= " << Players[i]->get_turnsTaken() << endl;
	}
	for(int i=numHumans; i<numPlayers;i++){
		out << "BotID= " << i << endl;
		out << "param1= " << Players[numHumans+i]->get_param(0) << endl;
		out << "param2= " << Players[numHumans+i]->get_param(1) << endl;
		out << "param3= " << Players[numHumans+i]->get_param(2) << endl;
		out << "param4= " << Players[numHumans+i]->get_param(3) << endl;
		out << "Score= " << Players[numHumans+i]->get_score() << endl;
		out << "Turns= " << Players[numHumans+i]->get_turnsTaken() << endl;
		out << endl;
	}
	return 1;
}

void Farkle::playTurn(int playerID){
	bool turnOver=0;
	int numHeld=0;
	int turnScore=0;
	for(int i=0;i<6;i++){
		Dice[i].reset();
	}
	while(!turnOver){
		int results[6] = {0};
		for(int i=0;i<6;i++){		// roll and save results
			if(!Dice[i].get_held()){
				Dice[i].roll();
				results[i]= Dice[i].get_value();
			}
		}
		bool hold[6]={0};
		bool keepPoints = 0;
		if(validRoll(results)){
			Players[playerID]->chooseDice(results, hold, keepPoints);
			turnScore += scoreRoll(results, hold);
			if(keepPoints){
				turnOver=true;
				Players[playerID]->addpoints(turnScore);
			}
		}
		else{
			turnOver=true;
		}


	}
}

bool Farkle::playRound(){
	for(int i=0; i<numPlayers;i++){
		
	}
}