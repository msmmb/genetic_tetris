#include "brain.cpp"
#include <iostream>

class Population {
    public:
        vector<Brain> agents;
        int numAgents;
        
        Population();
        vector<float> normalize(vector<float> params);
        vector<float> brainCrossover(Brain brain1, Brain brain2);
        void generateNewPopulation();
};

Population::Population() {
    numAgents = 80;
    for (int a=0; a<numAgents; a++) {
        vector<float> params;
        for (int p=0; p<4; p++) {
            float param = (float)d(rd)/pow(10,7);
            param *= 2*(d(rd)%2)-1;
            params.push_back(param);
        }
        agents.push_back(Brain(params));
    }
}

vector<float> Population::brainCrossover(Brain brain1, Brain brain2) {
    vector<float> p1 = brain1.params;
    vector<float> p2 = brain2.params;
    float f1 = brain1.score;
    float f2 = brain2.score;
    vector<float> newParams;
    for (int i=0; i<4; i++) newParams.push_back((f1*p1[i]+f2*p2[i])/(f1+f2+pow(10, -10)));
    return newParams; 
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

        vector<float> offspringParams = brainCrossover(randomSelection[nSelection-1], randomSelection[nSelection-2]);
        Brain newBrain = Brain(offspringParams);
        if (d(rd)%100 < 5) newBrain.mutate();
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
    cout << "fittest agent: {";
    for (int p=0; p<3; p++) cout << agents.back().params[p] << ", ";
    cout <<  agents.back().params[3] << "}" << endl;
    cout << endl<< "#############################################################" << endl << endl << endl;
    
    for (int i=0; i<nWorstAgents; i++) agents[i] = newOffsprings[i];
}
