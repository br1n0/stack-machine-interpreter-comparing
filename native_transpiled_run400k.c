// 
// run the transpiled program 400k times for benchmark
// gcc native_transpiled_run1.c -o native_transpiled_run1
//
#include "transpiled_main.c"

int main(){
    for(long times=400000;times>0;times--)
		run();
}