

#ifndef FUNLIB_H
#define FUNLIB_H
#define short_int short int
enum Action {Hit ,Stand,Split , Double};

class State{
    public:
        short_int  process;/*< process --> 0 for start , 1 for middle , 2 for end*/
        short_int sum;/*< sum ---> 2 to 30 */
    public:
        State(){};
        State(short_int pr,short_int su){
            process = pr;
            sum = su;
        };
        // happy

};

class Dealer_State:public State{
    public:
        
};
#endif