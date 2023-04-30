#include "grid.cpp"

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


NeuralNetwork::NeuralNetwork() {
	int i, j;

	for(i=0; i<3; i++) {
		vector<float> tmp;
		for (j=0; j<4; j++) {
			tmp.push_back(getRandomParam());
		}
		layer1.push_back(tmp);
		biases1.push_back(getRandomParam());
	}

	for (i=0; i<3; i++) {
		layer2.push_back(getRandomParam());
	}
	bias2 = getRandomParam();
}

NeuralNetwork::NeuralNetwork(const char* fileName) {
	loadParams(fileName);
}

float NeuralNetwork::getRandomParam() {
	// returns random float between -1.0000000 and 1.0000000
	return  (float)d(rd)/pow(10,7)*(2*(d(rd)%2)-1);
}

float NeuralNetwork::reLU(float node) {
	if (node > 0.0) return node;
	return 0.0;
}

float NeuralNetwork::forward(vector<int> inputs) {
	float tmp, out = 0.0;

	for (int i=0; i<3; i++) {
		tmp = 0.0; 

		for (int j=0; j<4; j++) {
			tmp += inputs[j]*layer1[i][j]; 
		}

		out += reLU(tmp+biases1[i])*layer2[i];
	}

	return out+bias2;
}

void NeuralNetwork::saveParams(string fileName, int score) {
	int i, j;
    ofstream file(fileName);
    file << "";
    file.close();
    ofstream fileAdd;
    fileAdd.open(fileName, ios_base::app);

    for (i=0; i<3; i++) {
		for (j=0; j<4; j++) {
			fileAdd << layer1[i][j] << endl;
		}
		fileAdd << biases1[i] << endl;
	}
	for (i=0; i<3; i++) {
		fileAdd << layer2[i] << endl;
	}
	fileAdd << bias2 << endl;

	fileAdd << score;
	fileAdd.close();
}

void NeuralNetwork::loadParams(const char* fileName) {
	int i, j;
    char *line;
    size_t len = 0;
	FILE *file = fopen(fileName, "r");

	for (i=0; i<3; i++) {
		vector<float> tmp;
		for (j=0; j<4; j++) {
			getline(&line, &len, file);
			tmp.push_back((float)strtod(line, NULL));
		}
		layer1.push_back(tmp);
		getline(&line, &len, file);
		biases1.push_back((float)strtod(line, NULL));
	}
	for (i=0; i<3; i++) {
		getline(&line, &len, file);
		layer2.push_back((float)strtod(line, NULL));
	}
	getline(&line, &len, file);
	bias2 = (float)strtod(line, NULL);

	fclose(file);
}
