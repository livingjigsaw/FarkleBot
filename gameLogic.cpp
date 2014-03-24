//this defines at least the scoring function by the Farkle class, meant to keep 
//the many, many conditionals out of the main h file
#include "farkle.h"
#include <iostream>
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

void Farkle::playTurn(int playerID, bool isBotGame){
	bool turnOver=0;
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
			int numHeld = 0;
			for(int i=0;i<6;i++)
				if(hold[i]==1)
					Dice[i].hold();
			for(int i=0;i<6;i++)
				if(Dice[i].get_held())
					numHeld++;
			if(numHeld==6)
				for(int i=0;i<6;i++)
					Dice[i].reset();

			if(keepPoints){
				turnOver=true;
				Players[playerID]->addPoints(turnScore);
			}
		}
		else{
			turnOver=true;
			if(!isBotGame){
				cout <<"You Farkled!\n";
				for(int i=0;i<6;i++){
					if(results[i]!=0)
						cout << "Die number " << i << " shows a " << results[i] <<endl;
				}
				cout << endl;
			}
		}
	}
}

int Farkle::playRound(bool isBotGame){
	for(int i=0; i<numPlayers;i++){
		if(!isBotGame){
			cout << "It is Player " << i <<"'s turn\n";
			cout << "your current score is " << Players[i]->get_score() <<endl <<endl;
		}
		playTurn(i, isBotGame);
		Players[i]->addTurn();
		if(!isBotGame && Players[i]->get_score()>10000)
			return i;
	}
	return -1;
}

void Farkle::finalRound(int startID){
	int current = startID;
	current++;
	if(current == numPlayers)
		current=0;
	while(current != startID){
		playTurn(current, 0);	
		Players[current]->addTurn();
	}
}

bool Farkle::validRoll(int results[]){
	int tally[6]={0};
	for(int i=0;i<6;i++)
		if(results[i]!=0)
			tally[results[i]-1]++;
	int numPairs=0;
	for(int i=0;i<6;i++)
		if(tally[i]==2)
			numPairs++;

	if(tally[0]>0 || tally[4] >0)
		return 1;
	else if(tally[1]>2 || tally[2]>2 || tally[3]>2 || tally[5]>2)
		return 1;
	else if(tally[0]==1 && tally[1]==1 && tally[2]==1 && tally[3]==1 && tally[4]==1 && tally[5]==1)
		return 1;
	else if(numPairs==3)
		return 1;
	else
		return 0;//FARKLE!
}

int Farkle::scoreRoll(int results[], bool hold[]){
	int score=0;
	int tally[6]={0};
	for(int i=0;i<6;i++)
		if(hold[i])	//so only count what was held from roll
			tally[results[i]-1]++;

	int numPairs=0;
	int numTrips=0;
	int numQuads=0;
	int numPents=0;
	int numHexes=0;	//2 through 6 of a kinds
	bool straight=0;
	for(int i=0;i<6;i++){
		if(tally[i]==2)
			numPairs++;
		if(tally[i]==3)
			numTrips++;
		if(tally[i]==4)
			numQuads++;
		if(tally[i]==5)
			numPents++;
		if(tally[i]==6)
			numHexes++;
	}
	if(numHexes==1)
		score+=3000;
	if(numPents==1)
		score+=2000;
	if(numQuads==1){
		if(numPairs==1)
			score+=1500;
		else
			score+=1000;
	}
	if(numTrips==2)
		score+=1500;
	if(numPairs==3)
		score+=1500;
	if(tally[0]==1 && tally[1]==1 && tally[2]==1 && tally[3]==1 && tally[4]==1 && tally[5]==1){
		score+=1500;
		straight=1;
	}
	if(tally[0]==3 && numTrips!=2)
		score+=300;	
	if(tally[1]==3 && numTrips!=2)
		score+=200;	
	if(tally[2]==3 && numTrips!=2)
		score+=300;	
	if(tally[3]==3 && numTrips!=2)
		score+=400;	
	if(tally[4]==3 && numTrips!=2)
		score+=500;	
	if(tally[5]==3 && numTrips!=2)
		score+=600;
	if(tally[0]>0 && tally[0]<3 && numPairs !=3 && !straight)
		score+=100*tally[0];
	if(tally[4]>0 && tally[4]<3 && numPairs !=3 && !straight)
		score+=50*tally[4];

	return score;

}