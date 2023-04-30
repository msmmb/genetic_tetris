#include "brain.cpp"
#include <iostream>

class Population {
    public:
        vector<Brain> agents;
        int numAgents;
        
        Population();
        vector<float> normalize(vector<float> params);
        void generateNewPopulation();
};

Population::Population() {
    numAgents = 150;
    for (int a=0; a<numAgents; a++) {
		NeuralNetwork params;
        agents.push_back(Brain(params));
    }
}

void Population::generateNewPopulation() {
    vector<Brain> newOffsprings;
    int nWorstAgents = numAgents*0.3;
    int nSelection = numAgents*0.1;

    for (int i=0; i<nWorstAgents; i++) {
        vector<Brain> randomSelection;

        for (int j=0; j<nSelection; j++) {
            randomSelection.push_back(agents[d(rd)%numAgents]);
        }
        

        sort(randomSelection.begin(), randomSelection.end(),
        [](Brain & b1, Brain & b2 ) -> bool {
            return b1.score < b2.score;
        });

        Brain newBrain = randomSelection[nSelection-1].crossover(randomSelection[nSelection-2]);
        newOffsprings.push_back(newBrain);
    }
    sort(this->agents.begin(), this->agents.end(),
    [](Brain & b1, Brain & b2 ) -> bool {
        return b1.score < b2.score;
    });
     
    int totalFitness = 0;
    for (int a=0; a<numAgents; a++) totalFitness += agents[a].score;
    
    cout << "#############################################################" << endl << endl;
    cout << "average fitness: " << (float)totalFitness/numAgents << endl;
    cout << "highest fitness: " << agents.back().score << endl;
    cout << endl<< "#############################################################" << endl << endl << endl;
    
    for (int i=0; i<nWorstAgents; i++) agents[i] = newOffsprings[i];
}
