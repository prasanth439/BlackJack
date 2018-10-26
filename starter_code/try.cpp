#include<bits/stdc++.h>
using namespace std;

int main(){

    float b[10][100] = {{0}} ;
    int count = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<100;j++){
            if(b[i][j]!=0){
                count++;
            }
        }
    }
    cout<<count<<endl;
    return 0;   
}