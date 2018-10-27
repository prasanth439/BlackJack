#include "black_jack_solver.h"

BlackJackSolver::BlackJackSolver(float face_card_prob)
{
    this->face_card_prob = face_card_prob;
    this->normal_card_prob = (1.0f - face_card_prob)/9.0f;
    computeReward_Stand();
    computeReward_DoubleDown();

};
void BlackJackSolver::computeReward_Stand()
{
    int i,j;
    for(i=4;i<=21;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_stand[i][j] = valueStand(i,s);
        }
        j = 11;
        State s(j,1);
        reward_stand[i][j] = valueStand(i,s);

    }
};
float BlackJackSolver::valueStand(int hand_value,State dealer_hand)
{
    if(dealer_hand.sum>=17&&dealer_hand.sum<=21)
    {
        if(hand_value>dealer_hand.sum){
            return 1;
        }
        else if(hand_value==dealer_hand.sum){
            return 0;
        }
        else{
            return -1;
        }
    }
    else if(dealer_hand.sum>21&&dealer_hand.count_ace==0){
        return 1;
    }
    else if(dealer_hand.sum>21){
        dealer_hand.sum -=10;
        dealer_hand.count_ace--;
        return valueStand(hand_value,dealer_hand);
    }
    else{

        int i;
        float answer=0.0f;
        for(i = 2;i<10;i++){

            dealer_hand.sum +=i;
            answer +=  normal_card_prob * valueStand(hand_value,dealer_hand);
            dealer_hand.sum -=i;
        }
        // for i = 11
        i = 10;
        dealer_hand.sum+=i;
        answer +=face_card_prob * valueStand(hand_value,dealer_hand);
        dealer_hand.sum -=i;

        i = 11;
        dealer_hand.sum +=i;
        dealer_hand.count_ace++;
        answer +=  normal_card_prob * valueStand(hand_value,dealer_hand);
        dealer_hand.sum -=i;
        dealer_hand.count_ace--;

        if(answer<-1){
            cout<<hand_value<<"  "<<dealer_hand.sum<<endl;
            cout<<" exitting "<<endl;
            cout<<answer<<endl;
            exit(1);
        }
        return answer;

    }
};


void BlackJackSolver::printOutput(vector<vector<char>>& answer_diff,vector<vector<char>>& answer_ace,vector<vector<char>>& answer_pair)
{

    // temporary variables
    int i,j;

    //----> For DiffValue
    for ( i = 5 ; i <= 19 ; i++ ) {
        cout<<i<<"\t";
        for( j = 0 ; j < 10 ; j++ ){
            cerr<<i-5<<" =========== "<<endl;
            cout<<answer_diff[i-5][j]<<" ";
        }
        cout<<"\n";
    }
    //----> For AceValue
    for ( i = 2 ; i <= 9 ; i++ ) {
        cout<<"A"<<i<<"\t";
        for( j = 0 ; j < 10 ; j++ ){
            cout<<answer_ace[i-2][j]<<" ";
        }
        cout<<"\n";
    }
    //----> For pairs
    for ( i = 2 ; i <= 10 ; i++ ) {
        cout<<i<<i<<"\t";
        for( j = 0 ; j < 10 ; j++ ){
            cout<<answer_pair[i-2][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"AA\t";
    for( j = 0 ; j < 10 ; j++ ){
        cout<<answer_pair[9][j]<<" ";
    }

    return ;
};
