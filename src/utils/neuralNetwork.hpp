#include <vector>
#include <string>

using namespace std;

#ifndef NN_H
#define NN_H

class NeuralNetwork {
	public:
		// 4x3x1 neural network
		vector<vector<float>> layer1; 
		vector<float> biases1;
		vector<float> layer2;
		float bias2;
		
		NeuralNetwork();
		NeuralNetwork(const char* fileName);
		float getRandomParam();
		float reLU(float node);
		float forward(vector<int> inputs);
		void saveParams(string fileName, int score);
		void loadParams(const char* fileName);
}; 

#endif