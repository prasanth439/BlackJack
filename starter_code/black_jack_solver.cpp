#include "black_jack_solver.h"
#include "hide.h"

void BlackJackSolver::computeReward_DoubleDown()
{
    int i,j;
    for(i=4;i<=20;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_doubledown[i][j] = valueDoubleDown(i,s);
        }
        j = 11;
        State s(j,1);
        reward_doubledown[i][j] = valueDoubleDown(i,s);
    }
};

void BlackJackSolver::computeReward_DoubleDown_Ace(){
    // kalfdjl
    int i,j;
    for(i=13;i<=20;i++){
        for(j=2;j<11;j++){
            State s(j,0);
            reward_doubledown_Ace[i][j] = valueDoubleDown_ace(i,s);
        }
        j = 11;
        State s(j,1);
        reward_doubledown_Ace[i][j] = valueDoubleDown_ace(i,s);
    }
};

float BlackJackSolver::valueDoubleDown(int hand_value,State dealer_hand)
{

    int i;
    float answer = 0.0f;
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
            answer += -2*face_card_prob;
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
            // busted
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
            answer += normal_card_prob*2.0f*reward_stand[hand_value-10][dealer_hand.sum];
        }
        else{
            answer += normal_card_prob * 2.0f * reward_stand[hand_value][dealer_hand.sum];
        }
        hand_value -=i;
}

void BlackJackSolver::computeValue(){
    // one value is reward 1.5
    float val[20] = {0},val_aus[21] = {0},val_pair[21] = {0},val_no_double[22] = {0},val_aus_no_double[22] = {0};
    float next_val[20] = {0},next_val_aus[21] = {0},next_val_pair[21] = {0},next_val_no_double[22] = {0},next_val_aus_no_double[22] = {0};
    vector<vector<char>> answer_diff(15,vector<char>(10,'A')),answer_ace(15,vector<char>(8,'A')),answer_pair(10,vector<char>(10,'A'));
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
    int dealer_card ;
    for(dealer_card = 2;dealer_card<=11;dealer_card++){
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
                hit(answer_diff,i-5,dealer_card-2);
            else if(val[i]==reward_stand[i][dealer_card])
                stand(answer_diff,i-5,dealer_card-2);
            else
                doubleDown(answer_diff,i-5,dealer_card-2);
        }
        for(i=13;i<=20;i++){
            if(val_aus[i]==temp_qh_aus[i])
                hit(answer_ace,i-13,dealer_card-2);
            else if(val_aus[i]==reward_stand[i][dealer_card]){
                stand(answer_ace,i-13,dealer_card-2);
            }
            else if(val_aus[i]==reward_doubledown_Ace[i][dealer_card])
                doubleDown(answer_ace,i-13,dealer_card-2);
        }
        for(i=4;i<=22;i=i+2)
        {
            if(val_pair[i]==temp_qh[i])
                hit(answer_pair,(i/2)-2,dealer_card-2);
            else if(val_pair[i]==reward_stand[i][dealer_card]){
                stand(answer_pair,(i/2)-2,dealer_card-2);
            }
            else if(val_pair[i]==reward_doubledown[i][dealer_card])
                doubleDown(answer_pair,(i/2)-2,dealer_card-2);       
            else if(val_pair[i] == temp_qp[i])
                pairVal(answer_pair,(i/2)-2,dealer_card-2);     
        }
        // for AA


    }
    printOutput(answer_diff,answer_ace,answer_pair);
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
