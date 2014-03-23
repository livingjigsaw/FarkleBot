#include <list>

class Genome{
	private:
		double eval;
		double opponentScoreRatio;
		double myScoreRatio;

	public:
		Genome();
		~Genome();
		void randomStart();
		void evaluation();
		double fitness(double avg);
};

class Genetic{
	private:
		list<Genome> geneSet;
		double average;
	public:
		Genetic();
		~Genetic();
		void step();
		void fitness();
		void breed();
		Genome crossover(Genome first, Genome second);
		Genome mutate(Genome toMutate);
		Genome cataclysmicMutate(Genome toMutate);
		boolean converge();
};
