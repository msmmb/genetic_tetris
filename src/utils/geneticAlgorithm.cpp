#include "population.cpp"

class GeneticAlgorithm {
    
    public:
        int gen;
        int bestRecordedFitness;
        Population population;
        
        GeneticAlgorithm();
        void runGeneticAlgorithm();
        Brain runGames(Brain brain);
};

GeneticAlgorithm::GeneticAlgorithm() {
    gen = 1;
    int l = 1;
    char *line;
    size_t len = 0;
    FILE *file1 = fopen("../data/bestParams.txt", "r");
    while (getline(&line, &len, file1) != -1) {
        if (l++ == 5) bestRecordedFitness = atoi(line); 
    }
    fclose(file1);
}


void GeneticAlgorithm::runGeneticAlgorithm() {
    while(1) {
        int agent = 0;
        float bestFitness = population.agents[0].score;

        for (int b=0; b<population.numAgents; b++) {
            population.agents[b] = runGames(population.agents[b]);
            if (bestFitness < population.agents[b].score) {
                bestFitness = population.agents[b].score; 
            }
            cout << "gen " << gen << "   agent " << ++agent << "/" << population.numAgents;
            cout << "  current -> " << population.agents[b].score << "  best -> " << bestFitness << endl;;
        }
        cout << endl << endl << "GENERATION " << gen++ << endl << endl; 
        population.generateNewPopulation();
    }
}

Brain GeneticAlgorithm::runGames(Brain brain) {
    int nGames = 7;
    int fitness = 0;

    cout << endl << "current agent -> {";
    for (int p=0; p<3; p++) cout << brain.params[p] << ", ";
    cout <<  brain.params[3] << "}" << endl;

    for (int g=0; g<nGames; g++) {
        Grid grid;
        int pieces = 0;
        while (!grid.gameOver && pieces++ < 10000) {
            string bestMove = brain.getBestMove(grid);
            int bestRotation = (int)bestMove.back()-48;
            bestMove.pop_back();
            
            for (int i=0; i<bestRotation; i++) grid.rotatePiece();

            if (bestMove[0] == 'r') {
                for (int m=0; m<bestMove.size(); m++) grid.movePiece(1,9);
            } else {
                for (int m=0; m<bestMove.size(); m++) grid.movePiece(-1,0);
            } 
            
            grid.gravity(3);
            grid.clearLine();
            grid.piece.newShape();
            grid.piece.newNext();
        }
        cout << "game " << g+1 << " ->  score: " << grid.score << "  lines: " << grid.clearedLines << endl;
        fitness += grid.score;
    }

    brain.score = fitness/nGames;

    if (brain.score > bestRecordedFitness) {
        bestRecordedFitness = brain.score;
        ofstream file("../data/bestParams.txt");
        file << "";
        file.close();
        ofstream fileAdd;
        fileAdd.open("../data/bestParams.txt", ios_base::app);
        for (int p=0; p<4; p++) fileAdd << brain.params[p] << endl;
        fileAdd << brain.score;
        fileAdd.close();
    }
    
    return brain;
}