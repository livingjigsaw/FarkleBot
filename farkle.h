//functionality
#include <ctime>
#include <math.h>
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
		void addTurn(){turnsTaken++;};
		//methods
		void addPoints(int points){score=score+points;};
		int scoreRoll(int results[], bool hold[]);
		bool validHold(int results[], bool hold[]);	// this makes sure the held dice are legitimate.
		virtual void chooseDice(int* rollResults, bool* hold, bool& keepPoints, int turnScore){};	//humans and bots will do this differently


};

class FarkleBot:public Player{
	public:
		FarkleBot(){};
		virtual ~FarkleBot(){};

		virtual void chooseDice(const int* diceValues, bool* toHold, bool& keep, int turnScore){};	//this is where the decision of which dice the bot keeps, 0's in the array are not counted
		virtual void saveAI(){}; //writes ai to file
		virtual void readAI(){}; //reads AI from file
}; 

class Human:public Player{				// handles io for humans to play
	public:
		Human(){};
		~Human(){};

		void chooseDice(int rollResults[], bool* hold, bool& keepPoints, int turnScore);	//humans and bots will do this differently

}; 

class DrewBot:public FarkleBot{
	public:
		DrewBot(){};
		~DrewBot(){};
		void chooseDice(const int* diceValues, bool* toHold, bool& keep, int turnScore);
		void saveAI();
		void readAI();
};

class LizBot:public FarkleBot{
	public:
		LizBot(){};
		~LizBot(){};
		void chooseDice(const int* diceValues, bool* toHold, bool& keep, int turnScore);
		void saveAI();
		void readAI();
};

class ShouseBot:public FarkleBot{
	private:
		double* params;	
		/*
		param 1 weights num of dice
		param 2 weights roll's score
		param 3 weights turn score
		param 4 weights leading opponent's score **not implementing this right now** this is difficult to do with current game's implementation! not passing in data from other players currently
		*/
	public:
		ShouseBot(){
			params=new double [3];
			params[0]=rand()%10;
			params[1]=rand()%10;
			params[2]=rand()%10;
		};
		~ShouseBot(){delete [] params;};

		double get_param(int paramID){return params[paramID];};
		void set_param(int paramID, double val){params[paramID]=val;};

		void chooseDice(const int* diceValues, bool* toHold, bool& keep, int turnScore);
		void saveAI(){};
		void readAI(){};
/*
			here i define a complicated system for finding the next generation. 
			I think this way would have a high chance of giving us very good results
			as well as lots of data we could export to a ROOT macro for nice data display
			this is something to shoot for, but will be in separate git branch for future development if we have time

			we should propogate next generation using numbers from multiple of the best bots from the previous game. 
			to do so, we should find the average parameter values of these x best bots
			then, we should also find the range of each parameter over x botsest bots
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

class ShouseAlgorithm{
	friend class PlayerFactory;
	private:
		int numBots;	//might do math with this
		ShouseBot** myBots;
	public:
		ShouseAlgorithm(int inBots){numBots=inBots;myBots=new ShouseBot* [numBots];};
		~ShouseAlgorithm(){delete [] myBots;};

		void Breed(){
			int numMax = ceil(numBots/20); //determining how many bots to average, don't want non-int
			double** max=new double*[numMax];
			for(int i=0;i<numMax;i++){
				max[i]=new double[4];	// 1st is score, 2 3 4 are params
			}
			for(int i=0;i<numBots;i++){
				double temp = myBots[i]->get_score();	// if score is greater than max score, save params from bot to array
				if(max[0][0]<temp){
					for(int j=numMax-1;j>0;j--){
						max[j][0]=max[j-1][0];
						max[j][1]=max[j-1][1];
						max[j][2]=max[j-1][2];
						max[j][3]=max[j-1][3];
					}
					max[0][0]=temp;
					max[0][1]=myBots[i]->get_param(0);
					max[0][2]=myBots[i]->get_param(1);
					max[0][3]=myBots[i]->get_param(2);
				}
			}
			double avg[3]={};
			for(int i=0;i<numMax;i++){
				avg[0]+=max[i][1];
				avg[1]+=max[i][2];
				avg[2]+=max[i][3];
			}
			avg[0]= avg[0]/numMax;
			avg[1]= avg[1]/numMax;
			avg[2]= avg[2]/numMax;
			myBots[0]->set_param(0, avg[0]);
			myBots[0]->set_param(1, avg[1]);
			myBots[0]->set_param(2, avg[2]);
			for(int i=1;i<numBots;i++){
				myBots[i]->set_param(0, myBots[0]->get_param(0)+((rand()%40)/10.0)-2);
				myBots[i]->set_param(1, myBots[0]->get_param(1)+((rand()%40)/10.0)-2);
				myBots[i]->set_param(2, myBots[0]->get_param(2)+((rand()%40)/10.0)-2);

			}
		};
};

class Farkle;

class PlayerFactory{	//factory class that makes the players
	private:
		int numHuman;
		int numDrewBot;
		int numLizBot;
		int numShouseBot;
	public:
		PlayerFactory(){};
		~PlayerFactory(){};

		void set_players(int inHuman, int inDrewBot, int inLizBot, int inShouseBot);
		void makePlayers(Farkle& game, ShouseAlgorithm& SA); // passes info to the farkle class
		Player* makeHuman(){Player* temp=new Human();return temp;};
		Player* makeDrewBot();
		Player* makeLizBot();
		ShouseBot* makeShouseBot(){ShouseBot* temp=new ShouseBot();return temp;};
};

class Farkle{					//handles game logic, turn stuff, players and holds the genetic algorithm for the next round
	friend class PlayerFactory;
	private:
		int numRounds;			// how many games will be played, mainly for training purposes
		int numPlayers;
		Die* Dice;				//becomes new Die[6];
		Player** Players;		//becomes new Player[x], where x = numPlayers, but cannot be allocated at once as it will contain bots and humans (hence the **)
	public:
		//construct/destruct
		Farkle();	// needs to create same things as other constructor
		~Farkle();
		
		bool saveResults(string filename);	// writes scores to a txt file
		void playTurn(int playerID, bool isBotGame);	
		int playRound(bool isBotGame);	//if player saves score over 10000, go to final round by returning that player's ID, or -1 otherwise
		void finalRound(int startID); 	//not used for bot training, as we want turns till 10000 and don't want turn order to skew results 
		bool validRoll(int results[]);	// this checks a group of results to see if points were saved. really to make sure people didn't make a mistake
		bool validHold(int results[], bool hold[]);	// this makes sure the held dice are legitimate.
		int scoreRoll(int results[], bool hold[]);
		void playHumans(); // a game with human players, with a final round
		void trainBots();	// this game does not have a final round, it continues until x number of bots pass 10000
		
};	
