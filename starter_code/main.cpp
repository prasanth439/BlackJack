
#include<bits/stdc++.h>
#include"black_jack_solver.h"
#define M 22
#define L 12
using namespace std;
int main(int argc,char* argv[]){
    float f_c_p;
    f_c_p= stof(argv[1]);
    BlackJackSolver b_solver = BlackJackSolver(f_c_p);
    // b_solver.printRewardValues();
    b_solver.computeValue();
    // testing
    // b_solver.printRewardValues();
    return 0;
}