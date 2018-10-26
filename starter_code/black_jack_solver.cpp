

#include "black_jack_solver.h"
BlackJackSolver::BlackJackSolver(float face_card_prob)
{
    this->face_card_prob = face_card_prob;
    this->normal_card_prob = (1.0f - face_card_prob)/9.0f;
    computeReward_Stand();
    computeReward_DoubleDown();
};
void BlackJackSolver::computeReward_Stand(){
    
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
void BlackJackSolver::computeReward_DoubleDown(){
    int i,j;
    for(i=4;i<=21;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_doubledown[i][j] = valueDoubleDown(i,s);
        }
        j = 11;
        State s(j,1);
        reward_stand[i][j] = valueDoubleDown(i,s);
    }
};
float BlackJackSolver::valueStand(int player_value,State s_value)
{
    
    if(s_value.sum>17)
    {
        if(s_value.sum>21){
            return 1;
        }
        if(player_value>s_value.sum){
            return 1;
        }
        else if(player_value==s_value.sum){
            return 0;
        }
        else{
            return -1;
        }
    }
    else
    {
        int i;
        float answer=0.0f;
        for(i = 2;i<10;i++){
            s_value.sum +=i;

            answer +=  normal_card_prob * valueStand(player_value,s_value);

            s_value.sum -=i;
        }
        // for i = 11
        i = 10;
        s_value.sum+=i;
        answer +=face_card_prob * valueStand(player_value,s_value);
        s_value.sum -=i;

        i = 11;
        if(s_value.count_ace!=0){
            i = 1;
        }
        s_value.sum +=i;
        if(i==11){
            s_value.count_ace++;
        }

        answer +=  normal_card_prob * valueStand(player_value,s_value);
        s_value.sum -=i;

        return answer;

    }
}
float BlackJackSolver::valueDoubleDown(int player_value,State s_value){

    int i;
    float answer = 0.0f;
    for(i=2;i<10;i++){
        player_value +=i;
        if(player_value>21){
            answer += -2*normal_card_prob;
        }
        else{
            answer += normal_card_prob * 2 * reward_stand[player_value][s_value.sum];
        }

        player_value -=i;
    }
    i=10;
        player_value +=i;
        if(player_value>21){
            answer += -2*face_card_prob;
        }
        else{
            answer += face_card_prob *2* reward_stand[player_value][s_value.sum];
        }

        player_value -=i;
    i=11;
        player_value +=i;
        if(player_value>21){
            player_value -=10;
            i = 1;
        }
        if(player_value>21){
            answer += -2*face_card_prob;
        }
        else{

            answer += normal_card_prob * 2*reward_stand[player_value][s_value.sum];
        }

        player_value -=i;
        return answer;

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