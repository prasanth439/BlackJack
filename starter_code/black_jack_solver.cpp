#include "black_jack_solver.h"
#include"hide.h"
void BlackJackSolver::computeValue(){
    // one value is reward 1.5
    float val[20] = {0},val_aus[21] = {0},val_pair[23] = {0},val_no_double[22] = {0},val_aus_no_double[22] = {0};
    float next_val[20] = {0},next_val_aus[21] = {0},next_val_pair[23] = {0},next_val_no_double[22] = {0},next_val_aus_no_double[22] = {0};
    vector<vector<char>> answer_diff(15,vector<char>(10,'A')),answer_ace(15,vector<char>(8,'A')),answer_pair(10,vector<char>(10,'A'));
    int j,i;
    int count = 1000;
    float max_;
    float temm;
    int temm_tt;
    float temp_qp[22],temp_qh[22];
    float temp_qh_aus[22];
    float qs,qh,qp,qd;
    int dealer_card ;
    for(dealer_card = 2;dealer_card<=11;dealer_card++){
        count = 0;
        // value iteration 
        while(count<1500){
            // temp_qh  --> 4 to 20
            val[21]=val_aus[21]=val_aus_no_double[21]=val_no_double[21] = reward_stand[21][dealer_card];
            for(i=4;i<=21;i++)
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
                
                    temm_tt = i+j;
                    if (temm_tt>21)
                        temm += face_card_prob*(-1.0f);
                    else
                    {
                        temm += face_card_prob*val_no_double[temm_tt];
                    }
                
                j = 11;
                
                    temm_tt = i+j;
                    if(temm_tt<=21){
                        temm+= normal_card_prob*val_aus_no_double[temm_tt];
                    }
                    else{
                        // temm+= normal_card_prob*val_no_double[temm_tt-10];
                        temm_tt-=10;
                        if(temm_tt<=21){
                            temm+= normal_card_prob*val_no_double[temm_tt];
                        }
                        else{
                            temm+= normal_card_prob*(-1.0f);
                        }
                    }
                
                temp_qh[i] = temm;
            }
            // temp_qh_aus
            for(i=13;i<=21;i++)
            {
                // find the qh qs q
                temm = 0;
                for(j=1;j<10;j++){
                    temm_tt = i+j;
                    if (temm_tt>21){
                        temm += normal_card_prob*val_no_double[temm_tt-10];
                    }
                    else
                    {
                        temm += normal_card_prob*val_aus_no_double[temm_tt];
                    }
                }
                j = 10;
                
                    temm_tt = i+j;
                    if (temm_tt>21)
                        temm += face_card_prob*val_no_double[temm_tt-10];
                    else
                    {
                        temm += face_card_prob*val_aus_no_double[temm_tt];
                    }
                
                temp_qh_aus[i] = temm;
                
            }
            // temp_qp
            for(i=4;i<=22;i=i+2)
            {
                temm = 0;
                for(j=2;j<10;j++){
                    if(i/2==j){
                        temm += normal_card_prob*val_pair[i]; 
                    }
                    else{
                        temm_tt = i/2 + j;
                            temm += normal_card_prob * val[temm_tt];
                    }
                }
                j=10;
                    if(i/2==j){
                        temm += face_card_prob*val_pair[i]; 
                    }
                    else{
                        temm_tt = i/2 + j;
                        temm += face_card_prob * val[temm_tt];
                        
                    }
                j=11;
                    temm_tt = i/2 + j;
                    if(temm_tt==22){
                        temm += normal_card_prob * val_aus[temm_tt-10];
                    }
                    else{
                        temm += normal_card_prob * val_aus[temm_tt];
                    }
                    temm = 2*temm;
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
            for(i=13;i<=20;i++)
            {
                max_ = reward_stand[i][dealer_card];
                if(max_<reward_doubledown_Ace[i][dealer_card]){
                    max_ = reward_doubledown_Ace[i][dealer_card];
                }
                if(max_<temp_qh_aus[i]){
                    max_ = temp_qh_aus[i];
                }
                next_val_aus[i] = max_;           
            }
            // val pair
            for(i=4;i<=22;i=i+2){
                if(i==22){
                    i-=10;
                    max_ = reward_stand[i][dealer_card];
                    if(max_<reward_doubledown_Ace[i][dealer_card]){
                        max_ = reward_doubledown_Ace[i][dealer_card];
                    }
                    if(max_<temp_qh_aus[i]){
                        max_ = temp_qh_aus[i];
                    }
                    if(max_<temp_qp[i]){
                        max_ = temp_qp[i];
                    }
                    next_val_pair[i] = max_;   
                    break;     
                }
                else{
                    max_ = reward_stand[i][dealer_card];
                    if(max_<reward_doubledown[i][dealer_card]){
                        max_ = reward_doubledown[i][dealer_card];
                    }
                    if(max_<temp_qh[i]){
                        max_ = temp_qh[i];
                    }
                    if(max_<temp_qp[i]){
                        max_ = temp_qp[i];
                    }
                    next_val_pair[i] = max_;                     
                }

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
            i = 22;
                val_pair[22] = next_val_pair[22];
            count++;
        }
        // first action finding
        // different cards
        for(i=5;i<=19;i++){
            if(val[i]==temp_qh[i])
                hit(answer_diff,i-5,dealer_card-2);
            else if(val[i]==reward_stand[i][dealer_card])
                stand(answer_diff,i-5,dealer_card-2);
            else if(val[i]==reward_doubledown[i][dealer_card])
                doubleDown(answer_diff,i-5,dealer_card-2);
            if(i==11&&dealer_card==10){
                cerr<<"Value["<<i<<"]["<<dealer_card<<"] Value | Qhit | Qstand | Qdoubledown"<<endl;
                cerr<<val[i]<<"  "<<temp_qh[i]<<"  "<<reward_stand[i][dealer_card]<<"  "<<reward_doubledown[i][dealer_card]<<endl;
            }
        }
        // ace cards
        for(i=13;i<=20;i++){
            if(val_aus[i]==temp_qh_aus[i])
                hit(answer_ace,i-13,dealer_card-2);
            else if(val_aus[i]==reward_stand[i][dealer_card]){
                stand(answer_ace,i-13,dealer_card-2);
            }
            else if(val_aus[i]==reward_doubledown_Ace[i][dealer_card])
                doubleDown(answer_ace,i-13,dealer_card-2);
            else{
                cerr<<"ValueAus["<<i<<"]["<<dealer_card<<"] Value | Qhit | Qstand | Qdoubledown"<<endl;
                cerr<<val_aus[i]<<"  "<<temp_qh[i]<<"  "<<reward_stand[i][dealer_card]<<"  "<<reward_doubledown[i][dealer_card]<<endl;
            }
        }
        // pairs
        for(i=4;i<=22;i=i+2)
        {
            if(val_pair[i]==temp_qh[i])
                hit(answer_pair,(i/2)-2,dealer_card-2);
            else if(val_pair[i]==reward_stand[i][dealer_card]){
                stand(answer_pair,(i/2)-2,dealer_card-2);
            }
            else if(val_pair[i]==reward_doubledown[i][dealer_card])
                doubleDown(answer_pair,(i/2)-2,dealer_card-2);       
            else if(val_pair[i]==temp_qp[i])
                pairVal(answer_pair,(i/2)-2,dealer_card-2);
            else{
                cerr<<"ValuePair["<<i<<"]["<<dealer_card<<"] Value | Qhit | Qstand | Qdoubledown | QPair"<<endl;
                cerr<<val_pair[i]<<"  "<<temp_qh[i]<<"  "<<reward_stand[i][dealer_card]<<"  "<<reward_doubledown[i][dealer_card]<<"  "<<temp_qp[i]<<endl;
            }   
        }



    }
    printOutput(answer_diff,answer_ace,answer_pair);
};

