#include <iostream>
#include <sstream>
#include <vector>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"
#include "bossa_timer.h"

std::vector<std::vector<double> > points;

int main(int argc, char* argv[]) {

	

	unsigned n = 0;			// size of chromosomes
	const unsigned p = 10;		// size of population
	const double pe = 0.15;		// fraction of population to be the elite-set
	const double pm = 0.05;		// fraction of population to be replaced by mutants
	const double rhoe = 0.80;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding

	// Reading instance
	std::string s;

	int n_points, dim;
	std::getline(std::cin, s);
	std::stringstream st(s);
	st >> n_points >> dim;

	points = std::vector<std::vector<double> > (n_points);
	for(unsigned i=0; i<n_points; ++i)
		points[i] = std::vector<double> (dim);


	//std::vector<double> CLUSTER_L(dim);
	//std::vector<double> CLUSTER_U(dim);

	//for(int d=0;d<dim;++d) {
		//CLUSTER_L[d] = 1000;
		//CLUSTER_U[d] = -1000;
	//}

	for(int i=0;i<n_points;++i) {

		std::getline(std::cin, s);
		std::stringstream st(s);
		for(int d=0; d<dim; ++d) {
			st >> points[i][d];

			//if(CLUSTER_L[d] > points[i][d])
				//CLUSTER_L[d] = points[i][d]; //Min da dim
			//if(CLUSTER_U[d] < points[i][d])
				//CLUSTER_U[d]  = points[i][d]; //Max da dim
		}



	}

	
	


	SampleDecoder decoder;			// initialize the decoder



	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator

	n = n_points+1;
	
	// initialize the BRKGA-based heuristic


	BossaTimer timer;
	timer.start();
	
	double bestValue = -1;
	double timerToBest;
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 50;	// run for 1000 gens
	do {
		algorithm.evolve();	// evolve the population for one generation

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}

		std::cout << "It " << generation << "Best objective value = "
	 		<< (-1)*algorithm.getBestFitness() << std::endl;
	
	if(bestValue < (-1)*algorithm.getBestFitness()){
		bestValue = (-1)*algorithm.getBestFitness();
		timerToBest = timer.getTime();
		}

	} while (generation < MAX_GENS);
	timer.pause();

	std::cout << "Best solution found has objective value = "
	 		<< (-1)*algorithm.getBestFitness() << std::endl;
		std::cout << "Total time = " << timer.getTime() << std::endl;
		std::cout << "Time to Best ttb = " << timerToBest << std::endl;


	return 0;
}
