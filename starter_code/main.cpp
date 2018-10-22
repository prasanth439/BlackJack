

#include"black_jack_solver.h"
#include<string>
int main(int argc,char argv[]){
    float f_c_p;
    f_c_p = stof(argv[0]);
    cout<<f_c_p<<endl;
    BlackJackSolver b_solver = BlackJackSolver(f_c_p);
    return 0;
}