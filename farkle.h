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
	protected:
		int score;
		int turnsTaken;
		bool keepCurrentTurn;	// 0 means I choose to roll again, 1 means I shall keep my points.
		
	public:
		//struction
		Player(){score=0;turnsTaken=0;};
		virtual ~Player(){};
		//getters
		int get_score(){return score;};
		int get_turnsTaken(){return turnsTaken;};
		//methods
		void addPoints(int points){score=score+points;}
		virtual void holdDice(int* rollResults, int numRolled){};	//humans and bots will do this differently
		virtual void set_param(int paramID, double input){};
		virtual double get_param(int paramID){return 0;};


};

class Farkle{					//handles game logic, turn stuff, players and holds the genetic algorithm for the next round
	private:
		int numBots;
		int numHumans;	
		int numPlayers;		//if == 0, the game becomes a bot training match 
		int numRounds;			// how many games will be played, mainly for training purposes
		Die* Dice;				//becomes new Die[6];
		Player** Players;		//becomes new Player[x], where x = numPlayers, but cannot be allocated at once as it will contain bots and humans (hence the **)
		int activePlayer; 		// index of who's turn it is
		int activeTurnScore; 	// score of current dice rolls
	public:
		//construct/destruct
		Farkle(){};	// needs to create same things as other constructor
		Farkle(int inBots, int inHumans, int inNumRounds);
		~Farkle();
		bool readAI(string filename, int botID);		//reads the AI param settings from a genetic algorithm from file; botID = place in array relative to other bots 0 indexed
		bool storeAI(string filename, int botID);		//stores the AI param settings from a genetic algorithm into output file;
		bool saveResults(string filename);	// writes scores to a txt file
		void playTurn(int playerID);
		bool playRound();	//if player saves score over 10000, go to final round by returning 1
		void finalRound();  
		bool validRoll(int[] results);	// this checks a group of results to see if points were saved. really to make sure people didn't make a mistake
		int scoreRoll(int[] results, bool[] hold);
		void playHumans(); // a game with human players
		void trainBots();	// this takes instantiated bots in Players, deletes the losers, repopulates. this is the genetic algorithm!
		/*
			here i define a complicated system for finding the next generation. 
			I think this way would have a high chance of giving us very good results
			as well as lots of data we could export to a ROOT macro for nice data display
			this is something to shoot for, but will be in separate git branch for future development if we have time

			we should propogate next generation using numbers from multiple of the best bots from the previous game. 
			to do so, we should find the average parameter values of these x best bots
			then, we should also find the range of each parameter over x best bots
			next, propogate across range with higer percentage of bots within made closer to avg
			
			for example: we have 625 bots, and each parameter from the x best bots has an avg of 5, and a range of 4 (from 3 to 7)
			propagation would then do this: for each parameter a child would have params at 3, 4, 5, 6, 7 of each other parameter
			this is why we need 625, because we varied each of 4 params 5 times, 5^4 combinations
			the distrobution isn't gaussian, but not bad for approximation and "easier" because instead of finding variance
			all we have to do is find avg, find range, step = range/5, 
				params then made at avg - 2*step, avg - step, avg, avg+step, avg+2step
			this puts 3 out of 5 children within 40% of the mean, quite close to forcing a gaussian distribution of children
		*/
		

};	

class FarkleBot:public Player{			//implements the ai behavior, stores parameters,
	private:
		double* params; // points to array of AI parameters
		/*
		here are the parameters tracked in game:
			opponent's score / 10000
			maximum opponent's score - my score / 10000; the bigger, the riskier we'll be as we are farther behind
			current turn's score / 1000; 
			number of dice left to roll/6
			
		the params should be a double from 0-1 that the results from above are multiplied with, moving towards a final decision 

		the AI scores every possibility of each roll score against these parameters
		*/
	public:
		FarkleBot(){params = new double[4]; params[0] = 0;params[1] = 0;params[2] = 0;params[3] = 0;};
		//FarkleBot(double* inParams); //not sure if this is needed
		~FarkleBot(){delete [] params;};

		double get_param(int paramID){return params[paramID];};
		void set_param(int paramID, double input){params[paramID] = input;};
		void chooseDice(int* diceValues, bool& toHold, bool& keep);	//this is where the decision of which dice the bot keeps, 0's in the array are not counted
}; 

class Human:public Player{				// handles io for humans to play
	public:
		Human(){};
		~Human(){};

}; 
