#include "farkle.h"
#include <iostream>
using namespace std;

void Human::chooseDice(int rollResults[], bool hold[], bool& keepPoints){
	cout << "You rolled the following: \n";
	for(int i=0;i<6;i++){
		if(rollResults[i]!=0)
			cout << "Die number " << i << " shows a " << rollResults[i]<<endl;
	}
	cout << endl;
	cout << "Which dice would you like to keep?\n";
	cout << "Enter in the dice numbers, then enter -1 when finished\n";
	int temp=0;
	do{
		cin >> temp;
		//could do validation here, but that's low priority
		hold[temp] = true;
	}while(temp !=-1);

	char decide;
	bool validInput = 0;
	while(!validInput){
		cout << "Would you like to keep rolling? y/n\n";
		cin >> decide;
		if(decide=='Y' || decide=='y'){
			keepPoints = false;
			validInput=true;
		}
		else if(decide=='N' || decide=='n'){
			keepPoints = true;
			validInput=true;
		}
		else
			cout << "Please enter a valid input\n";
	}
}

void Farkle::playHumans(){
	int playerOver= -1;
	while(playerOver == -1){
		playerOver=playRound(0);
	}
	finalRound(playerOver);
	int winner = playerOver;
	for(int i=playerOver;i!=playerOver;++i){	// by starting at playerOver, only players who rolled first win in case of a tie, as you must exceed a current winner past 10000 to beat them
		if(i==numPlayers)
			i=0;
		if(Players[i]->get_score() > Players[winner]->get_score())
			winner = i;	
	}
	cout << "Player " << winner+1 << "won the game!\n";
}

