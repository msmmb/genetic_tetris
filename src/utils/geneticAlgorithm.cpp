#include <string>
#include <iostream>
#include "geneticAlgorithm.hpp"

# define N_GAMES 3

GeneticAlgorithm::GeneticAlgorithm() {
    gen = 1;
    int l = 0;
    char *line;
    size_t len = 0;
    FILE *file1 = fopen("data/bestParams.txt", "r");
    while (getline(&line, &len, file1) != -1) {
        if (l++ == 4*3+3+3+1) bestRecordedFitness = atoi(line); 
    }
    fclose(file1);
}


void GeneticAlgorithm::runGeneticAlgorithm() {
    while(1) {
        int agent = 0;
        float bestFitness = population.agents[0].score;

        for (int b=0; b<population.numAgents; b++) {
            cout << "gen " << gen << "   agent " << ++agent << "/" << population.numAgents << endl;
            population.agents[b] = runGames(population.agents[b]);
            if (bestFitness < population.agents[b].score) {
                bestFitness = population.agents[b].score; 
            }
            cout << "current -> " << population.agents[b].score << "  best -> " << bestFitness << endl << endl;
        }
        cout << endl << endl << "GENERATION " << gen++ << endl << endl; 
        population.generateNewPopulation();
    }
}

Brain GeneticAlgorithm::runGames(Brain brain) {
    int fitness = 0;

    for (int g=0; g<N_GAMES; g++) {
        Grid grid;
        int pieces = 0;
        while (!grid.gameOver && pieces++ < 50000) {
            string bestMove = brain.getBestMove(grid);
            int bestRotation = (int)bestMove.back()-48;
            bestMove.pop_back();
            
            for (int i=0; i<bestRotation; i++) grid.rotatePiece();

            if (bestMove[0] == 'r') {
                for (int m=0; m<bestMove.size(); m++) grid.movePiece(1,9);
            } else {
                for (int m=0; m<bestMove.size(); m++) grid.movePiece(-1,0);
            } 
            
            while (!grid.piece.fixed) {
                grid.gravity(1);
                grid.clearLine();
                grid.update();
            }

            grid.piece.newShape();
            grid.piece.newNext();
        }
        cout << "game " << g+1 << " ->  score: " << grid.score << "  lines: " << grid.clearedLines << endl;
        fitness += grid.score;
    }

    brain.score = fitness/N_GAMES;

    if (brain.score > bestRecordedFitness) {
        bestRecordedFitness = brain.score;
		brain.params.saveParams("data/bestParams.txt", brain.score);
    }
    
    return brain;
}
