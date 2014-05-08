#include "farkle.h"
#include <iostream>
using namespace std;

void Human::chooseDice(int rollResults[], bool* hold, bool& keepPoints, int turnScore){
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
bool Player::validHold(int results[], bool held[]){
	int tally[6]={0};
	bool validDice[6]={0};
	for(int i=0;i<6;i++){
		if(results[i]!=0){
			if(held[i]){
				tally[results[i]-1]++;//only tally the dice that are held

			}
			else
				validDice[i]=1; //any dice not being held can't affect the hold
		}
		else{
			validDice[i]=1; //any dice not being rolled cannot make the choice invalid
		}
	}
	int numQuads =0;
	int numPairs=0;
	for(int i=0;i<6;i++){
		if(tally[i]==4)
			numQuads++;
		if(tally[i]==2)
			numPairs++;
	}

	if((tally[0]==1&&tally[1]==1&&tally[2]==1&&tally[3]==1&&tally[4]==1&&tally[5]==1)||(numPairs==3)||(numQuads==1&&numPairs==1)){
		validDice[0]=1;
		validDice[1]=1;
		validDice[2]=1;
		validDice[3]=1;
		validDice[4]=1;
		validDice[5]=1;
	}

	for(int i=0;i<6;i++){
		if(tally[i]>=3){
			for(int j=0;j<6;j++){
				if(results[j]-1 == i)
					validDice[j]=1;
			}
		}
		if(results[i]==1 || results[i]==5)
			validDice[i]=1;
	}

	for(int i=0;i<6;i++){
		if(validDice[i]!=1)
			return false;
	}

	return true;

}

int Player::scoreRoll(int results[], bool hold[]){
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

void ShouseBot::chooseDice(const int* diceValues, bool* toHold, bool& keep, int turnScore){
	int botScore[64]={};//this scores each possibility
	int rollScore[64]= {};
	double diceTally[64]={};
	bool holdData[64][6];

	for(int i=0;i<64;i++){
		for(int j=0;j<6;j++){
			holdData[i][j]=0;
		}
	}

	int tempVals[6];
	for(int i=0;i<6;i++){
		tempVals[i]=diceValues[i];
	}

	int count=0;
	for(int i=0;i<2;i++){		
		for(int j=0;j<2;j++){	
			for(int k=0;k<2;k++){
				for(int l=0;l<2;l++){
					for(int m=0;m<2;m++){	
						for(int n=0;n<2;n++){
							holdData[count][0]=i;
							holdData[count][1]=j;
							holdData[count][2]=k;
							holdData[count][3]=l;
							holdData[count][4]=m;
							holdData[count][5]=i;
							count++;
						}
					}
				}
			}
		}
	}

	for(int i=0;i<64;i++){
		for(int j=0;j<6;j++){
			if(holdData[i][j]==1 && diceValues[j]==0)
				botScore[i]= -1;
		}

		if(botScore[i] >=0 && validHold(tempVals,holdData[i])){
			rollScore[i]=scoreRoll(tempVals, holdData[i]);
		
			for(int j=0;j<6;j++){
				if(tempVals[i]!=0 && holdData[i][j]==0)
					diceTally[i]++;
			}
		if(diceTally[i]==0)
			diceTally[i]=6;
		
		botScore[i]+=diceTally[i]*get_param(0)*10;
		botScore[i]+=rollScore[i]*get_param(1)/300.0;
		}
	

	}
	double maxScore=0;
	int maxIndex=0;
	for(int i=0;i<64;i++){
		if(botScore[i]>maxScore){
			maxScore=botScore[i];
			maxIndex=i;
		}
	}
	if(botScore[maxIndex] > turnScore*get_param(2)/10)
			keep=0;
		else
			keep=1;
		for(int i=0;i<6;i++){
			toHold[i]=holdData[maxIndex][i];
		}



}

/*  old AI functions, not used but may want the code for later

bool Farkle::readAI(string filename){
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
*/
