// i_TTC_dispatch_function_table.c
// Token Threaded Code Shared library - dispatch imeplemented with function table
// the functions are hot loaded using shared library, so it can be used as a genric DSL.
//
// compile shared library
// gcc -std=c99 -Ofast -fPIC -fvisibility=hidden  -shared vm_shared.c -o vm_shared.so -lm
//
// compile the main program
// gcc i_TTC_dispatch_function_table_shared.c -lm -o i_TTC_dispatch_function_table_shared
//
// run
// ./i_TTC_dispatch_function_table_shared

#include "vm.h"


int main(){
    VM vm = {0};
    hot_reload(&vm);
        
    long times=400000;
    for(;times>0;times--){
        //printf("times:%d\n",times);
        #include "test3.c"
        exec(&vm);
    }    

    return 0;
}