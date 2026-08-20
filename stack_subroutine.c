// 
// stack language: subroutine threaded
// gcc stack_subroutine.c -lm -o stack_subroutine
// 


// forward declaration
typedef struct VM VM;


// definisco un tipo puntatore a funzione void f(VM*)
typedef void (*Opcode)(VM *vm);


typedef struct VM VM;
#include "stack_common.h"


// ===== EXEC =====
void exec(VM *vm){
    while(vm->pc < vm->code_size){
        Opcode op = vm->code[vm->pc++];
        op(vm);
    }
}


// ======= opcode ======= 
void OP_NOP(VM *vm){
    printf("\npc=%d: OP_NOP\n", vm->pc-1);
}


void OP_RETURN(VM *vm){
    printf("\npc=%d: OP_RETURN R:%f\n",
           vm->pc-1,
           vm->stack[vm->sp-1]);

    vm->pc = vm->code_size; // termina VM
}


void OP_ADD(VM *vm){
    double a=0,b=0;
    b = stack_pop(vm);
    a = stack_pop(vm);
//    printf("\npc=%d: OP_ADD\n", vm->pc-1);
    stack_push(vm, a+b);
}


void OP_SUB(VM *vm){
    double a=0,b=0,r=0;
    a= stack_pop(vm);
    b= stack_pop(vm);
    r= a-b;
//    printf("\nOP_SUB[%d]\n", vm->sp);
//    printf("a:%f\n", a);
//    printf("b:%f\n", b);
//    printf("r:%f\n", r);
//    printf("\n");
    stack_push(vm, r);
}


void OP_MUL(VM *vm){
    double a=0,b=0,r=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
    r= a*b;
//    printf("\nOP_MUL[%d]\n", vm->sp);
//    printf("a:%f\n", a);
//    printf("b:%f\n", b);
//    printf("r:%f\n", r);
//    printf("\n");
    stack_push(vm, r);
}


void OP_DIV(VM *vm){
    double a=0,b=0;
    b = stack_pop(vm);
    a = stack_pop(vm);
//    printf("\npc=%d: OP_DIV\n", vm->pc-1);
    stack_push(vm, a/b);
}


void OP_SIN(VM *vm){
    double a=0,b=0;
    a = stack_pop(vm);
//    printf("\npc=%d: OP_DIV\n", vm->pc-1);
    stack_push(vm, sin(a));
}


void OP_COS(VM *vm){
    double a=0,b=0;
    a = stack_pop(vm);
//    printf("\npc=%d: OP_COS\n", vm->pc-1);
    stack_push(vm, cos(a));
}


int main(){
    VM vm = {0};

    long times=4000000;
    for(;times>0;times--){
        //printf("times:%d\n",times);
    #include "program3.c"
    }
 
    exec(&vm);

    return 0;
}
