#include "population.hpp"

#ifndef GA_H
#define GA_H

using namespace std;

class GeneticAlgorithm {
    
    public:
        int gen;
        int bestRecordedFitness;
        Population population;
        
        GeneticAlgorithm();
        void runGeneticAlgorithm();
        Brain runGames(Brain brain);
};

#endif