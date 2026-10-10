// 
// baseline number crunching of test3
// gcc native_baseline.c -o native_baseline
//

#include <stdio.h>


void run(){
    double r=0;
    for(int i=0;i<2000;i++) 
        r-= 1;
    r= r*2; 
}


int main(){

    for(long times=400000;times>0;times--)
        run();

    return 0;
}