#ifndef BLACK_JACK_SOLVER
#define BLACK_JACK_SOLVER
#include<vector>
#include<iostream>
using namespace std;
class BlackJackSolver{
    public:
        // some temporary variables
        float face_card_prob;

    public:
        BlackJackSolver(float );
        void printOutput(vector<vector<int>> &answer_diff,vector<vector<int>> &answer_ace,vector<vector<int>> &answer_pair);
        void run();
        
        // methods to implement
};
#endif