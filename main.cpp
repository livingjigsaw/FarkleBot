//farkle main
#include "farkle.h"
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));	// sets global random seed based on system time, VERY IMPORTANT, may move to Farkle class
	Die hand;
	Die band;
	Die sand;
	hand.roll();
	band.roll();
	sand.roll();
	cout << "hand val = " << hand.get_value() << endl;
	cout << "band val = " << band.get_value() << endl;
	cout << "sand val = " << sand.get_value() << endl;
	for (int i=0;i<20;i++){
		hand.reset();
		hand.roll();
		cout << "roll " << i << " = " << hand.get_value() << endl;
		}
}