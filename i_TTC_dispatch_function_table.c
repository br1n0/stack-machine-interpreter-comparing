// 
// stack language: function table based
// gcc stack_function_table.c -lm -o stack_function_table
//

#include "Opcode_enum.c"
typedef struct VM VM;

#include "common.h"

// variabili globali supporto, forse converrebbe metterle nelle  funzioni, in questo modo il codice diverrebbe thread safe
double a=0,b=0;



void (*table[OPCODE_COUNT])(VM *vm);


// ===== EXEC =====
double exec(VM *vm){

    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];
        ( table[op] )( vm );
    }
    //return vm->stack[0];
    return vm->stack[vm->sp-1];
}


// ======= opcode ======= 
void F_OP_NOP(VM *vm){
    printf("pc=%d: OP_NOP\n", vm->pc-1);
}


void F_OP_RETURN(VM *vm){
    //printf("pc=%d: OP_RETURN R:%f\n",
    //       vm->pc-1,
    //       vm->stack[vm->sp-1]);

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
    stack_push(vm, sin(a));
}


void F_OP_COS(VM *vm){
    a = stack_pop(vm);
    stack_push(vm, cos(a));
}



int main(){

    table[OP_NOP]= F_OP_NOP;
    table[OP_RETURN]= F_OP_RETURN;
    table[OP_ADD]= F_OP_ADD;
    table[OP_SUB]= F_OP_SUB;
    table[OP_MUL]= F_OP_MUL;
    table[OP_DIV]= F_OP_DIV;
    table[OP_SIN]= F_OP_SIN;
    table[OP_COS]= F_OP_COS;

    VM vm = {0};

    long times=400000;
    for(;times>0;times--){
        //printf("times:%d\n",times);
        #include "test3.c"
        exec(&vm);
    }    

    return 0;
}