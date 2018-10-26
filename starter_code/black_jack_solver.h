#ifndef BLACK_JACK_SOLVER_H
#define BLACK_JACK_SOLVER_H
#include<vector>
#include<iostream>
#include"funlib.h"
using namespace std;
class BlackJackSolver{
    public:
        // some temporary variables
        float face_card_prob;

    public:
        BlackJackSolver(float );
        void printOutput(vector<vector<int>> &answer_diff,vector<vector<int>> &answer_ace,vector<vector<int>> &answer_pair);
        void run();
        float evaluator(short_int number);
        float evaluateWrapper(short_int number);
        
        // methods to implement
};
#endif