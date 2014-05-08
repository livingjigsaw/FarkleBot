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
