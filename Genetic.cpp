#include "Genetic.h"
#include <iostream>
#include <cassert>
using namespace std;

Genome::Genome(){

}

Genome::Genome(const Genome& other){
	for(int i = 0; i < 4; i++){
		ratios[i] = other.ratios[i];
	}
	
}

Genome::~Genome(){

}

double Genome::randomNum(){
	return ((double) rand() / (RAND_MAX));
}

void Genome::randomStart(){
	for(int i = 0; i < 4; i++){
		ratios[i] = randomNum();
	}
}

int Genome::evaluate(){
	eval = 1;
	return 1;
}

double Genome::fitness(double avg){
	return eval/avg;
}

void Genome::setN(int index, double ratio){
	ratios[index] = ratio;
}

double Genome::getN(int index) const{
	return ratios[index];
}
//////////////////////////////////////////////////////////////////////////////////

Genetic::Genetic(int size){

	randomStart(size);
}

Genetic::~Genetic(){

}

void Genetic::randomStart(int setSize){
	Genome temp;
	for(int i = 0; i < setSize; i++){
		temp = Genome();
		temp.randomStart();
		geneSet.push_back(temp);
	}
}

void Genetic::evaluate(){
	int sum = 0;
	for(list<Genome>::iterator it = geneSet.begin(); it != geneSet.end(); it++){
		sum += it->evaluate();
	}
	average = sum/geneSet.size();
	assert(average == 1);
}

void Genetic::breed(){
	list<Genome> intermediateSet;
	list<Genome> nextGeneration;
	double odds;
	int guaranteedTimes;
	double possibility;
	Genome temp;
	for(list<Genome>::iterator it = geneSet.begin(); it != geneSet.end(); it++){
		odds = it->fitness(average);
		guaranteedTimes = (int)odds;
		possibility = odds - guaranteedTimes;
		for(int i = 0; i < guaranteedTimes; i++){
			temp = Genome(*it);
			intermediateSet.push_back(temp);
		}
		if(possibility <= it->randomNum()){
			temp = Genome(*it);
			intermediateSet.push_back(temp);
		}
	}
	list<Genome>::iterator previous;
	cout << "intermediate " << intermediateSet.size() << endl;
	for(list<Genome>::iterator it = intermediateSet.begin(); it != intermediateSet.end(); it++){
		if(it == intermediateSet.begin()){
			previous = it;
			continue;
		}
		nextGeneration.push_back(crossover(*previous, *it));
		previous = it;
	}
	geneSet = nextGeneration;
}

Genome Genetic::crossover(const Genome& first, const Genome& second){
	Genome crossedOverGene = Genome();
	for(int i = 0; i < 4; i++){
		if(rand() % 2 == 0){
			crossedOverGene.setN(i, first.getN(i));
		}
		else{
			crossedOverGene.setN(i, second.getN(i));
		}
	}
	return crossedOverGene;
}

bool Genetic::converge(){
	cout << "set " << geneSet.size() << endl;
	return geneSet.size() == 1;
}

void Genetic::step(){
	evaluate();
	breed();
}