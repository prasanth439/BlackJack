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
        float normal_card_prob;
        float reward_stand[22][10] = {{0.0}};
        float reward_doubledown[22][10] = {{0.0}};

    public:
        BlackJackSolver(float );
        void printOutput(vector<vector<int>> &answer_diff,vector<vector<int>> &answer_ace,vector<vector<int>> &answer_pair);
        void run();
        void computeReward_Stand();
        float valueStand(int player_value,State s_value);
        float BlackJackSolver::valueDoubleDown(int player_value,State s_value);

        void computeReward_DoubleDown();
        
        // methods to implement
};
#endif