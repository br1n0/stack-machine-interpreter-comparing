//void (*table[OPCODE_COUNT])(VM *vm);

/*
compile as library
gcc -std=c99 -Ofast -fPIC -fvisibility=hidden  -shared vm_shared.c -o vm_shared.so -lm


nm -D --defined-only vm_shared.so
0000000000003e00 D vm_api

#to interpretate the answer of nm:
#D for data
#T for function

*/
#include<math.h>
#include "vm.h"


// ======= opcode ======= 
void F_OP_NOP(VM *vm){
double a=0,b=0;
    printf("pc=%d: OP_NOP\n", vm->pc-1);
}


void F_OP_RETURN(VM *vm){
    double a=0,b=0;
    //printf("pc=%d: OP_RETURN R:%f\n",  vm->pc-1,  vm->stack[vm->sp-1]);

    vm->pc = vm->code_size; // termina VM
}


void F_OP_ADD(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
//    printf("pc=%d: OP_ADD\n", vm->pc-1);
    stack_push(vm, a+b);
}


void F_OP_SUB(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
//    printf("pc=%d: OP_SUB\n", vm->pc-1);
    stack_push(vm, a-b);
}


void F_OP_MUL(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
    stack_push(vm, a*b);
}


void F_OP_DIV(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
    stack_push(vm, a/b);
}


void F_OP_SIN(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    stack_push(vm, sin(a));
}


void F_OP_COS(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    stack_push(vm, cos(a));
}


EXPORT const VM_API vm_api = {
    .version = 1,
    .size = 6,
    .table= {
        F_OP_NOP,
        F_OP_RETURN,
        F_OP_ADD,
        F_OP_SUB,
        F_OP_MUL,
        F_OP_DIV,
        F_OP_SIN,
        F_OP_COS
    }
};
