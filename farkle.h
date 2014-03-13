//functionality
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

class Die{			// should be complete 3/12
	private:
		int value;
		bool held;		//0 = roll again, 1 = held
	public:
		//construct/destruct
		Die(){value = 0; held = 0;};
		~Die(){};
		//getters
		int get_value(){return value;};
		bool get_held(){return held;};
		//smethods
		void hold(){held=1;};
		void reset(){value=0;held=0;};
		void roll(){						//because just random isn't good enough
			int vals[100] = {};
			for(int i=0; i<100; i++){
				vals[i] = rand();
			}
			int choice=rand()%100; 			// 101st from the seed, happens to be prime to lower chances of repeats skipping factors
			value = vals[choice]%6+1;
		}
}; 

class Player{		//parent class for bots and humans
	private:
		int score;
		int turnsTaken;
		bool keepCurrentTurn;	// 0 means I choose to roll again, 1 means I shall keep my points.
	public:
		


};

class Farkle{					//handles game logic, turn stuff, players and holds the genetic algorithm for the next round
	private:
		int numPlayers;
		int numHumans;			//if == 0, the game becomes a bot training match 
		int numRounds;			// how many games will be played, mainly for training purposes
		Die* Dice;				//becomes new Die[6];
		Player* Players;		//becomes new Player[x], where x = numPlayers
		int activePlayer; 		// index of who's turn it is
		int activeTurnScore; 	// score of current dice rolls
	public:
		void readAI(){};		//reads the AI param settings from a genetic algorithm from file;
		void storeAI(){};		//stores the AI param settings from a genetic algorithm into output file;
};

class FarkleBot:public Player{			//implements the ai behavior, stores parameters,

}; 

class Human:public Player{				// handles io for humans to play

}; 
