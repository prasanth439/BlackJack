

#ifndef FUNLIB_H
#define FUNLIB_H

class State{
    public:
        int sum;
        int count_ace;
    public:
        State(){};
        State(int sum,int count_ace){
            this->sum = sum;
            this->count_ace = count_ace;
        };
};

#endif