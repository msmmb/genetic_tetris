#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "utils/brain.cpp"

using namespace std;

int main() {
    
    char *line;
    size_t len = 0;
    int l = 1;
    FILE *file1 = fopen("../data/bestParams.txt", "r");
    vector<float> bestParams;
    FILE *file2 = fopen("../data/record.txt", "r");
    int record;
    bool newRecord = false;

    while (getline(&line, &len, file1) != -1) {
        if (l++ < 5) bestParams.push_back((float)strtod(line, NULL));
    }
    fclose(file1);

    if (getline(&line, &len, file2) != -1) record = atoi(line);
    fclose(file2);

    Grid grid;
    Brain brain(bestParams);
    string bestM;
    bool fixed = false;
    bool rotated = false;
    string bestMove = brain.getBestMove(grid);
    int bestRotation = (int)bestMove.back()-48;
    bestMove.pop_back();

    while (!grid.gameOver) {

       if (!rotated) {
           for (int i=0; i<bestRotation; i++) grid.rotatePiece();
           rotated = true;     
       }

       if (bestMove.size() > 0) {
           if (bestMove[0] == 'r') {
                grid.movePiece(1,9);
                bestMove.pop_back();
           } else {
                grid.movePiece(-1,0);
                bestMove.pop_back();
           }
        }
       
       if (fixed) {
           bestMove = brain.getBestMove(grid);
           bestRotation = (int)bestMove.back()-48;
           bestMove.pop_back();
           bestM = bestMove;
           rotated = false;
           fixed = false; 
       }

       grid.gravity(1);
       grid.clearLine();
       grid.update();

        if (grid.piece.fixed) {
            grid.piece.newShape();
            grid.piece.newNext();
            fixed = true;
        }


        if (newRecord) cout << "NEW RECORD" << endl;
        cout << "cleared lines -> " << grid.clearedLines << endl;
        cout << "record -> " << record << endl << endl;
        if (bestM[0] == 'r') cout << "best move -> " << bestM.size() << " time(s) right and " << bestRotation << " rotation(s)" << endl;
        else if (bestM[0] == 'l') cout << "best move -> " << bestM.size() << " time(s) left and " << bestRotation << " rotation(s)" << endl;
        else cout << "best move -> don`t move and " << bestRotation << " rotation(s)" << endl;
        cout << endl;
        for (int j=4; j<24; j++) {
            for (int i=0; i<10; i++) {
                if (grid.matrix[j][i] == 0) {
                    cout << "· ";   
                } else {
                    cout << grid.matrix[j][i] << " ";
                }
            }
            cout << endl;
        }
        cout << endl << endl;
        
        if (grid.clearedLines > record) {
            newRecord = true;
            ofstream file("../data/record.txt");
            if (file.is_open()) {
                record = grid.clearedLines;
                file << record;
                file.close();
            }
        }
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return 0;
}
