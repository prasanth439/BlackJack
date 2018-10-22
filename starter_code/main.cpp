

#include"black_jack_solver.h"
using namespace std;
int main(int argc,char* argv[]){
    float f_c_p;
    f_c_p= stof(argv[1]);
    BlackJackSolver b_solver = BlackJackSolver(f_c_p);
    return 0;
}