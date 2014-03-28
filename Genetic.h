#include <list>
#include <cstdlib>
using namespace std;

class Genome{
	private:
		double eval;
		double ratios[4];
		// double playerScoreRatio;
		// double leaderScoreRatio; //player other than self who is in the lead
		// double currentTurnScoreRatio;
		// double diceNumberRatio;

	public:
		Genome();
		Genome(const Genome& other);
		~Genome();
		void randomStart();
		int evaluate();
		double fitness(double avg);
		void mutate();
		void cataclysmicMutate();
		double randomNum();
		void setN(int index, double ratio);
		double getN(int index) const;
};

class Genetic{
	private:
		list<Genome> geneSet;
		double average;
	public:
		Genetic(int size);
		~Genetic();
		void randomStart(int setSize);
		void step();
		void evaluate();
		void breed();
		Genome crossover(const Genome& first, const Genome& second);
		bool converge();
};
