Genome::Genome(){

}

Genome::~Genome(){

}

void Genome::randomStart(){

}

void Genome::evaluation(){
	return 1;
}

double fitness(double avg){
	return eval/avg;
}
//////////////////////////////////////////////////////////////////////////////////

Genetic::Genetic(){
	geneSet = new list<Genome> geneSet;
}