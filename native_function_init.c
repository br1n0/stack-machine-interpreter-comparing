// 
// stack language: function table based
// gcc stack_function_table.c -lm -o stack_function_table
//

#include "Opcode_enum.c"
typedef struct VM VM;

#include "common.h"

// variabili globali supporto, forse converrebbe metterle nelle  funzioni, in questo modo il codice diverrebbe thread safe
double a=0,b=0;




// ======= opcode ======= 
void F_OP_NOP(VM *vm){
    printf("pc=%d: OP_NOP\n", vm->pc-1);
}


void F_OP_RETURN(VM *vm){
    //printf("pc=%d: OP_RETURN R:%f\n", vm->pc-1, vm->stack[vm->sp-1]); //commentato voglio solo misurare il tempo di calcolo non lentezza stdout

    vm->pc = vm->code_size; // termina VM
}


void F_OP_ADD(VM *vm){
    a = stack_pop(vm);
    b = stack_pop(vm);
//    printf("pc=%d: OP_ADD\n", vm->pc-1);
    stack_push(vm, a+b);
}


void F_OP_SUB(VM *vm){
    a = stack_pop(vm);
    b = stack_pop(vm);
//    printf("pc=%d: OP_SUB\n", vm->pc-1);
    stack_push(vm, a-b);
}


void F_OP_MUL(VM *vm){
    a = stack_pop(vm);
    b = stack_pop(vm);
    stack_push(vm, a*b);
}


void F_OP_DIV(VM *vm){
    a = stack_pop(vm);
    b = stack_pop(vm);
    stack_push(vm, a/b);
}


void F_OP_SIN(VM *vm){
    a = stack_pop(vm);
//    stack_push(vm, sin(a));
    stack_push(vm, -(a));
}


void F_OP_COS(VM *vm){
    a = stack_pop(vm);
//    stack_push(vm, cos(a));
    stack_push(vm, -(a));
}


void run(){
    VM vm = {0};
    VM *v=&vm;    

    #include "test3_function_init.c"
}


int main(){

    for(long times=400000;times>0;times--){
        run();
    }    

    return 0;
}