#include"black_jack_solver.h"
BlackJackSolver::BlackJackSolver(float face_card_prob)
{
    this->face_card_prob = face_card_prob;
    this->normal_card_prob = (1.0f - face_card_prob)/9.0f;
    computeReward_Stand();
    computeReward_DoubleDown();
    computeReward_DoubleDown_Ace();
};
void BlackJackSolver::computeReward_Stand()
{
    int i,j;
    for(i=4;i<=21;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_stand[i][j] = valueStand(i,s,0);
        }
        j = 11;
        State s(j,1);
        reward_stand[i][j] = valueStand(i,s,0);

    }
};

void BlackJackSolver::computeReward_DoubleDown()
{
    // correct
    int i,j;
    for(i=4;i<=20;i++){
        for(j=2;j<=11;j++){
            State s(j,(j-1)/10);
            reward_doubledown[i][j] = valueDoubleDown(i,s);
        }
    }
    i=21;
    for(j=2;j<12;j++){
        reward_doubledown[i][j] = -2;
    }
};

void BlackJackSolver::computeReward_DoubleDown_Ace()
{
    // correct
    int i,j;    
    for(i=13;i<=20;i++){
        for(j=2;j<12;j++){
            State s(j,(j-1)/10);
            reward_doubledown_Ace[i][j] = valueDoubleDown_ace(i,s);
        }
    }
    i=21;
    for(j=2;j<12;j++){
        reward_doubledown_Ace[i][j] = -2;
    }
};
// hand 11 --> 10
float BlackJackSolver::valueDoubleDown(int hand_value,State dealer_hand)
{
    int i;
    float answer = 0.0f;
    //if(hand_value==21) return -2;
    for(i=2;i<10;i++){
        hand_value +=i;
        if(hand_value>21){
            // busted
            answer += -2*normal_card_prob;
        }
        else{
            answer += normal_card_prob * 2 * reward_stand[hand_value][dealer_hand.sum];
        }
        hand_value -=i;
    }
    i=10;
        hand_value +=i;
        if(hand_value>21){
            answer += -2*face_card_prob;
        }
        else{
            answer += face_card_prob *2* reward_stand[hand_value][dealer_hand.sum];
        }
        hand_value -=i;
    i=11;
        hand_value +=i;
        if(hand_value>21){
            hand_value -=10;
            i = 1;
        }
        if(hand_value>21){
            answer += -2*normal_card_prob;
        }
        else{
            answer += normal_card_prob * 2*reward_stand[hand_value][dealer_hand.sum];
        }

        hand_value -=i;
        return answer;

};

float BlackJackSolver::valueDoubleDown_ace(int hand_value,State dealer_hand)
{
    int i;
    float answer = 0.0f;
    for(i=1;i<10;i++){
        hand_value +=i;
        if(hand_value>21){
            answer += normal_card_prob*2.0f*reward_stand[hand_value-10][dealer_hand.sum];
        }
        else{
            answer += normal_card_prob * 2.0f * reward_stand[hand_value][dealer_hand.sum];
        }
        hand_value -=i;
    }
    i = 10;
        hand_value +=i;
        if(hand_value>21){
            // busted
            answer += face_card_prob*2.0f*reward_stand[hand_value-10][dealer_hand.sum];
        }
        else{
            answer += face_card_prob * 2.0f * reward_stand[hand_value][dealer_hand.sum];
        }
        hand_value -=i;
        return answer;
};
float BlackJackSolver::valueStand(int hand_value,State dealer_hand,int caller)
{//21 , 10
    if(caller==1&&dealer_hand.sum==21){
        return -1;
    }
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
        return valueStand(hand_value,dealer_hand,caller+1);
    }
    else{

        int i;
        float answer=0.0f;
        for(i = 2;i<10;i++){

            dealer_hand.sum +=i;
            answer +=  normal_card_prob * valueStand(hand_value,dealer_hand,caller+1);
            dealer_hand.sum -=i;
        }
        // for i = 11
        i = 10;
        dealer_hand.sum+=i;
        answer +=face_card_prob * valueStand(hand_value,dealer_hand,caller+1);
        dealer_hand.sum -=i;

        i = 11;
        dealer_hand.sum +=i;
        dealer_hand.count_ace++;
        answer +=  normal_card_prob * valueStand(hand_value,dealer_hand,caller+1);
        dealer_hand.sum -=i;
        dealer_hand.count_ace--;
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
        for( j = 0 ; j < 9 ; j++ ){
            //cerr<<i-5<<" =========== "<<endl;
            cout<<answer_diff[i-5][j]<<" ";
        }
        j = 9;
        cout<<answer_diff[i-5][j]<<"\n";
    }
    //----> For AceValue
    for ( i = 2 ; i <= 9 ; i++ ) {
        cout<<"A"<<i<<"\t";
        for( j = 0 ; j < 9 ; j++ ){
            cout<<answer_ace[i-2][j]<<" ";
        }
        j = 9;
        cout<<answer_ace[i-2][j]<<"\n";
    }
    //----> For pairs
    for ( i = 2 ; i <= 10 ; i++ ) {
        cout<<i<<i<<"\t";
        for( j = 0 ; j < 9 ; j++ ){
            cout<<answer_pair[i-2][j]<<" ";
        }
        cout<<answer_pair[i-2][j]<<"\n";
    }
    cout<<"AA\t";
    for( j = 0 ; j < 9 ; j++ ){
        cout<<answer_pair[9][j]<<" ";
    }
    j = 9;
    cout<<answer_pair[9][j];
    return ;
};

inline void BlackJackSolver::hit(vector<vector<char>>& t,int i,int j){
    t[i][j] = 'H';
}
inline void BlackJackSolver::stand(vector<vector<char>>& t,int i,int j){
    t[i][j] = 'S';
}
inline void BlackJackSolver::doubleDown(vector<vector<char>>& t,int i,int j){
    t[i][j] = 'D';
}
inline void BlackJackSolver::pairVal(vector<vector<char>>& t,int i,int j){
    t[i][j] = 'P';
}
void BlackJackSolver::printRewardValues()
{
    cout<<"\t\t\tRewardStand"<<endl<<endl<<"\t";
    for(int k=2;k<12;k++){
        cout<<k<<"\t";
    }
    cout<<"\n";
    for(int i=4;i<22;i++){
        cout<<"\n"<<i<<"\t";
        for(int j=2;j<12;j++){

            cout<<setprecision(3)<<fixed<<this->reward_stand[i][j]<<"\t";
        }
    }
    cout<<endl;

    cout<<"\t\t\tRewardDoubleDown"<<endl<<endl<<"\t";
    for(int k=2;k<12;k++){
        cout<<k<<"\t";
    }
    cout<<"\n";
    for(int i=4;i<22;i++){
        cout<<"\n"<<i<<"\t";
        for(int j=2;j<12;j++){
            cout<<setprecision(3)<<fixed<<this->reward_doubledown_Ace[i][j]<<"\t";
        }
    }
    cout<<endl;

};
