
#include <cmath>
#include <cstdlib>
#include <bits/stdc++.h>
#include "grid.cpp"

class Brain {
    public:
        vector<float> params;
        int score;

        Brain(vector<float> params);
        string getBestMove(Grid grid);
        void mutate();
        vector<int> getColumnHeights(vector<vector<int>> grid);
        int getCompletedLines(vector<vector<int>> grid);
        int getAggregateHeight(vector<vector<int>> grid);
        int getBumpiness(vector<vector<int>> grid);
        int getHoles(vector<vector<int>> grid);
};

Brain::Brain(vector<float> params) {
    this->params = params;
    score = 0;
}

string Brain::getBestMove(Grid grid) {
    string bestMove, bestRotation;
    float maxScore = -pow(10.0, 5);
    int nRotations = grid.piece.shapeRotations[grid.piece.n];
    Grid startingGrid = grid;
    vector<string> possibleMoves = {"llll", "lll", "ll", "l", "rrrrr", "rrrr", "rrr", "rr", "r", ""}; 
    
    for (int r=0; r<nRotations; r++) {
        for(int m=0; m<10; m++) {

            grid = startingGrid;
            for (int i=0; i<r; i++) grid.rotatePiece();

            if (possibleMoves[m][0] == 'l') {
                for (int i=0; i<possibleMoves[m].size(); i++) grid.movePiece(-1,0);
            } else if (possibleMoves[m][0] == 'r') {
                for (int i=0; i<possibleMoves[m].size(); i++) grid.movePiece(1,9);
            }

            grid.gravity(3);
            vector<int> heuristics = {getAggregateHeight(grid.matrix), getCompletedLines(grid.matrix),
                                      getHoles(grid.matrix), getBumpiness(grid.matrix)};


            float score = 0.0;
            for (int i=0; i<4; i++) score += params[i]*heuristics[i]; 

            grid.piece.newShape();
            
            int nRotationsNext = grid.piece.shapeRotations[grid.piece.n];
            Grid nextStartingGrid = grid;
            
            for (int rNext=0; rNext<nRotationsNext; rNext++) {
                for (int mNext=0; mNext<10; mNext++) {

                    grid = nextStartingGrid;
                    for (int i=0; i<rNext; i++) grid.rotatePiece();

                    if (possibleMoves[mNext][0] == 'l') {
                        for (int i=0; i<possibleMoves[mNext].size(); i++) grid.movePiece(-1,0);
                    } else if (possibleMoves[mNext][0] == 'r') {
                        for (int i=0; i<possibleMoves[mNext].size(); i++) grid.movePiece(1,9);
                    }

                    vector<int> heuristics = {getAggregateHeight(grid.matrix), getCompletedLines(grid.matrix),
                                              getHoles(grid.matrix), getBumpiness(grid.matrix)};

                    for (int i=0; i<4; i++) score += params[i]*heuristics[i]; 
                    
                    if (score >= maxScore) {
                        maxScore = score;
                        bestMove = possibleMoves[m];
                        bestRotation = to_string(r);
                    }
                }
            }
        }
    }
    return bestMove + bestRotation;
}

void Brain::mutate() {
    params[d(rd)%4] += ((d(rd)%2)*2-1)*0.2;
}

vector<int> Brain::getColumnHeights(vector<vector<int>> grid) {
    vector<int> columnHeights;
    for (int col=0; col<10; col++) {
        int height = 20;
        for (int row=4; row<24; row++) {
            if (grid[row][col] != 0 && grid[row][col] != 1) break;
            else height--;
        }
        columnHeights.push_back(height);
    }
    return columnHeights;
}

int Brain::getCompletedLines(vector<vector<int>> grid) {
    int completedLines = 0;
    for (int l=0; l<24; l++) if (!contains(0,grid[l])) completedLines++;
    return completedLines;
}

int Brain::getAggregateHeight(vector<vector<int>> grid) {
    int sum = 0;
    vector<int> heights = getColumnHeights(grid);
    for(int i=0; i<10; i++) sum += heights[i];
    return sum;
}

int Brain::getBumpiness(vector<vector<int>> grid) {
    vector<int> heights = getColumnHeights(grid);
    int bumpiness = 0;
    for(int i=0; i<9; i++) bumpiness += abs(heights[i]-heights[i+1]);
    return bumpiness;
}

int Brain::getHoles(vector<vector<int>> grid) {
    int holes = 0;

    for(int row=23; row>3; row--) {
        vector<int> zeros = {0,0,0,0,0,0,0,0,0,0};
        if (grid[row] == zeros) return holes;
        
        for (int col=9; col>=0; col--) {
            bool covered = false;
            if (grid[row][col] == 0) {
                for (int r=row-1; r>3; r--) {
                    if (grid[r][col] != 0) {
                        covered = true;
                        break;
                    }
                }
                if (covered) holes++;
            }
        }
    }
    return holes;
}
