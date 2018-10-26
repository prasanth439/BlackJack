

#include "black_jack_solver.h"
BlackJackSolver::BlackJackSolver(float face_card_prob)
{
    this->face_card_prob = face_card_prob;
    run();
};
float BlackJackSolver::evaluateWrapper(short_int number){
    float sum = 0;
    short_int i = 0;
    for(i = 1;i<11;i++){
        sum = sum + evaluator(number + i);
    }
    sum = sum / 10.0f;
    return sum;
}
float BlackJackSolver::evaluator(short_int number){
    
    float sum = 0;
    if(number>17){
          
        return number;
    }

    int i;
    for(i = 1;i<10;i++){
        sum = sum + evaluator(number + i);
    }
    sum = sum * (1.0f-face_card_prob)/9.0f;
    i = 10;
    sum += face_card_prob*evaluator(number + i);
    return sum;

};
void BlackJackSolver::run(){
    
    vector<vector<int>> answer_diff,answer_ace,answer_pair;
    // solve the optimal play for the dealer


    
    // printOutput(answer_diff,answer_ace,answer_pair);
};

void BlackJackSolver::printOutput(vector<vector<int>>& answer_diff,vector<vector<int>>& answer_ace,vector<vector<int>>& answer_pair)
{

    // temporary variables
    int i,j;

    //----> For DiffValue
    for ( i = 5 ; i <= 19 ; i++ ) {
        cout<<i<<"\t";
        for( j = 0 ; j < 10 ; i++ ){
            cout<<answer_diff[i-5][j]<<" ";
        }
        cout<<"\n";
    }
    //----> For AceValue
    for ( i = 2 ; i <= 9 ; i++ ) {
        cout<<"A"<<i<<"\t";
        for( j = 0 ; j < 10 ; i++ ){
            cout<<answer_ace[i-2][j]<<" ";
        }
        cout<<"\n";
    }
    //----> For pairs
    for ( i = 2 ; i <= 10 ; i++ ) {
        cout<<i<<i<<"\t";
        for( j = 0 ; j < 10 ; i++ ){
            cout<<answer_pair[i-2][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"AA\t";
    for( j = 0 ; j < 10 ; i++ ){
        cout<<answer_pair[9][j]<<" ";
    }

    return ;
};