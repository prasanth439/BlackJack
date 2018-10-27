

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
        bottle_neck =true;
        State s(j,1);
        reward_stand[i][j] = valueStand(i,s);
        if(i==21&&j==11){
            cout<<reward_stand[i][j]<<endl;
        }

    }
};


void BlackJackSolver::computeReward_DoubleDown()
{
    int i,j;
    for(i=4;i<=21;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_doubledown[i][j] = valueDoubleDown(i,s);
        }
        j = 11;
        State s(j,1);
        reward_doubledown[i][j] = valueDoubleDown(i,s);
    }
};
float BlackJackSolver::valueStand(int hand_value,State dealer_hand)
{
    // if(bottle_neck){
    //     cout<<dealer_hand.sum<<" "<<dealer_hand.count_ace<<endl;
    // }
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
}


void BlackJackSolver::printOutput(vector<vector<char>>& answer_diff,vector<vector<char>>& answer_ace,vector<vector<char>>& answer_pair)
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
float BlackJackSolver::valueDoubleDown(int hand_value,State dealer_hand)
{

    int i;
    float answer = 0.0f;
    for(i=2;i<10;i++){
        hand_value +=i;
        if(hand_value>21){
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
            answer += -2*face_card_prob;
        }
        else{

            answer += normal_card_prob * 2*reward_stand[hand_value][dealer_hand.sum];
        }

        hand_value -=i;
        return answer;

};
// void BlackJackSolver::computeReward_DoubleDown_Ace(){
//     int i;
//     float answer = 0.0f;
//     for(i=13;i<22;i++){
//         hand_value +=i;
//         if(hand_value>21){
//             answer += -2*normal_card_prob;
//         }
//         else{
//             answer += normal_card_prob * 2 * reward_stand[hand_value][dealer_hand.sum];
//         }

//         hand_value -=i;
//     }
//     i=10;
//         hand_value +=i;
//         if(hand_value>21){
//             answer += -2*face_card_prob;
//         }
//         else{
//             answer += face_card_prob *2* reward_stand[hand_value][dealer_hand.sum];
//         }

//         hand_value -=i;
//     i=11;
//         hand_value +=i;
//         if(hand_value>21){
//             hand_value -=10;
//             i = 1;
//         }
//         if(hand_value>21){
//             answer += -2*face_card_prob;
//         }
//         else{

//             answer += normal_card_prob * 2*reward_stand[hand_value][dealer_hand.sum];
//         }

//         hand_value -=i;
//         return answer;

// }

void BlackJackSolver::computeValue(){
    // one value is reward 1.5
    float val[20] = {0},val_aus[21] = {0},val_pair[21] = {0},val_no_double[22] = {0},val_aus_no_double[22] = {0};
    float next_val[20] = {0},next_val_aus[21] = {0},next_val_pair[21] = {0},next_val_no_double[22] = {0},next_val_aus_no_double[22] = {0};
    float min_diff;
    float EPSIOLON;
    // initialize the values of the states
    int j,i;
    int count = 300;
    float max_;
    float temm;
    int temm_tt;
    float temp_qp[22],temp_qh[22];
    float temp_qh_aus[22];
    float qs,qh,qp,qd;
    int dealer_card = 6;
    while(count<20){
        // temp_qh
        for(i=4;i<=19;i++)
        {
            // find the qh qs q
            temm = 0;
            for(j=2;j<10;j++){
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += normal_card_prob*(-1.0f);
                else
                {
                    temm += normal_card_prob*val_no_double[temm_tt];
                }
            }
            j = 10;
            {
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += face_card_prob*(-1.0f);
                else
                {
                    temm += face_card_prob*val_no_double[temm_tt];
                }
            }
            j = 11;
            {
                temm_tt = i+j;
                if(temm_tt<=21){
                    temm+= normal_card_prob*val_aus_no_double[temm_tt];
                }
                else{
                    temm+= normal_card_prob*val_no_double[temm_tt-10];
                }
            }
            temp_qh[i] = temm;
        }
        // temp_qh_aus
        for(i=13;i<=20;i++)
        {
            // find the qh qs q
            temm = 0;
            for(j=2;j<10;j++){
                temm_tt = i+j;
                if (temm_tt>21){
                    temm += normal_card_prob*val_no_double[temm_tt-10];
                }
                else
                {
                    temm += normal_card_prob*val_no_double[temm_tt];
                }
            }
            j = 10;
            {
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += face_card_prob*val_no_double[temm_tt-10];
                else
                {
                    temm += face_card_prob*val_no_double[temm_tt];
                }
            }
            j = 1;
            {
                temm_tt = i+j;
                if(temm_tt>21){
                    temm+= normal_card_prob*val_aus_no_double[temm_tt-10];
                }
                else{
                    temm+= normal_card_prob*val_no_double[temm_tt];
                }
            }
            temp_qh_aus[i] = temm;

            // find max and update
        }
        // temp_qp
        for(i=4;i<=20;i=i+2)
        {
            temm = 0;
            for(j=2;j<10;j++){
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += normal_card_prob*(-1.0f);
                else
                {
                    temm += normal_card_prob*val_no_double[temm_tt];
                }
            }
            j = 10;
            {
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += face_card_prob*(-1.0f);
                else
                {
                    temm += face_card_prob*val_no_double[temm_tt];
                }                
            }
            j = 11;
            {
                temm_tt = i+j;
                if (temm_tt>21)
                    temm += normal_card_prob*val_no_double[temm_tt-10];
                else
                {
                    temm += normal_card_prob*val_no_double[temm_tt];
                }    
            }
            temp_qp[i] = temm;
        }
        // val
        for(i=4;i<=20;i++)
        {
            max_ = reward_stand[i][dealer_card];
            if(max_<reward_doubledown[i][dealer_card]){
                max_ = reward_doubledown[i][dealer_card];
            }
            if(max_<temp_qh[i]){
                max_ = temp_qh[i];
            }
            next_val[i] = max_;
        }
        // val aus
        for(i=13;i<=21;i++)
        {
            max_ = reward_stand[i][dealer_card];
            if(max_<reward_doubledown[i][dealer_card]){
                max_ = reward_doubledown[i][dealer_card];
            }
            if(max_<temp_qh_aus[i]){
                max_ = temp_qh_aus[i];
            }
            next_val_aus[i] = max_;           
        }
        // val pair
        for(i=4;i<=20;i=i+2){
            max_ = reward_stand[i][dealer_card];
            if(max_<reward_doubledown[i][dealer_card]){
                max_ = reward_doubledown[i][dealer_card];
            }
            if(max_<temp_qh_aus[i]){
                max_ = temp_qh_aus[i];
            }
            if(max_<temp_qp[i]){
                max_ = temp_qp[i];
            }
            next_val_pair[i] = max_;             
        }
        // val no double
        for(i=4;i<=20;i++){
            max_ = reward_stand[i][dealer_card];
            if(max_<temp_qh[i]){
                max_ = temp_qh[i];
            }
            next_val_no_double[i] = max_;
        }
        // val aus no double
        for(i=13;i<=21;i++){
            max_ = reward_stand[i][dealer_card];
            if(max_<temp_qh_aus[i]){
                max_ = temp_qh_aus[i];
            }
            next_val_aus_no_double[i] = max_; 
        }


        // ============== transfer step ====== //
        for(i=0;i<20;i++){
            val[i]= next_val[i] ;
            val_aus[i] = next_val_aus[i];
            val_pair[i] = next_val_pair[i];
            val_no_double[i] = next_val_no_double[i];
            val_aus_no_double[i] = next_val_aus_no_double[i];
        }
        i = 20;
            val_aus[i] = next_val_aus[i];
            val_pair[i] = next_val_pair[i];
            val_no_double[i] = next_val_no_double[i];
            val_aus_no_double[i] = next_val_aus_no_double[i];
        i = 21;
            val_no_double[i] = next_val_no_double[i];
            val_aus_no_double[i] = next_val_aus_no_double[i];
        
        count++;
    }
    // action finding
    for(i=5;i<=19;i++){
        if(val[i]==temp_qh[i])
            hit();
        else if(val[i]==reward_stand[i][dealer_card])
            stand();
        else
            doubleDown();
    }
    for(i=13;i<=20;i++){
        if(val_aus[i]==temp_qh_aus[i])
            hit();
        else if(val_aus[i]==reward_stand[i][dealer_card]){
            stand();
        }
        else if(val_aus[i]==reward_doubledown[i][dealer_card])
            doubleDown();
    }
    for(;;){

    }
    // printOutput();
};
inline void BlackJackSolver::hit(){
    cout<<"H"<<endl;
}
inline void BlackJackSolver::stand(){
    cout<<"S"<<endl;
}
inline void BlackJackSolver::doubleDown(){
    cout<<"D"<<endl;
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

            cout<<setprecision(2)<<fixed<<this->reward_stand[i][j]<<"\t";
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
            cout<<setprecision(2)<<fixed<<this->reward_doubledown[i][j]<<"\t";
        }
    }
    cout<<endl;

};
