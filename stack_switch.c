/*
stack language, switch based
implementazione minimale

CODESTYLE:
poiche talvolta voglio commentare codice multilinea preferisco i commenti con //
preferisco utilizzare nella stessa linea { invece che accapo, per non generare troppoe linee

gcc stack_switch.c -lm -o stack_switch && ./stack_switch
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define STACK_MAX 2*1024
#define OPCODE_MAX 2*1024

typedef enum{
    OP_NOP,
    OP_RETURN,    
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_SIN,
    OP_COS
} Opcode;

typedef struct{
    double stack[ STACK_MAX ];
    Opcode code[ OPCODE_MAX ];
    int sp;
    int pc;
    int code_size;    
} VM;


static inline double stack_pop(VM *vm){
//    assert(vm->sp > 0);
//    assert(vm->sp < STACK_MAX);

    double d= vm->stack[--vm->sp];
 //   printf("stack_pop[%d]:%f\n", vm->sp,d );

    return d;
}

static inline void stack_push(VM *vm, double x){
//    printf("stack_push[%d]:%f\n", vm->sp+1,x );
//    assert(vm->sp < STACK_MAX);
    vm->stack[vm->sp++] = x;    
}

double exec(VM *vm){
    double a=0,b=0;


    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];

        switch(op){
            case OP_NOP:
                printf("pc=%d: OP_NOP\n", vm->pc - 1);
                break;

            case OP_RETURN:
                printf("pc=%d: OP_RETURN R:%f\n", vm->pc - 1, vm->stack[0]);
                return vm->stack[0];

            case OP_ADD:
                a = stack_pop(vm);
                b = stack_pop(vm);
                //printf("pc=%d: OP_ADD\n", vm->pc - 1);
                stack_push(vm, a + b);
                break;

            case OP_SUB:
                a = stack_pop(vm);
                b = stack_pop(vm);
                //printf("pc=%d: OP_SUB\n", vm->pc - 1);
                stack_push(vm, a - b);
                break;

            case OP_MUL:
                a = stack_pop(vm);
                b = stack_pop(vm);
                stack_push(vm, a * b);
                break;

            case OP_DIV:
                a = stack_pop(vm);
                b = stack_pop(vm);
                stack_push(vm, a / b);
                break;

            case OP_SIN:
                a = stack_pop(vm);
                stack_push(vm, sin(a));
                break;

            case OP_COS:
                a = stack_pop(vm);
                stack_push(vm, cos(a));
                break;

        }
    }
}

int main(){
/*
    VM vm = {0}; //resetto vm, dato che nop corrisponde a 0
    
    vm.stack[0]= 7;
    vm.stack[1]= 19;
    vm.stack[2]= 5;
    vm.stack[3]= 3;
    vm.sp = 4;

    vm.code_size=4;

    vm.code[0]= OP_ADD;
    vm.code[1]= OP_ADD;
    vm.code[2]= OP_SUB;
    vm.code[3]= OP_RETURN;
*/

    VM vm = {0};

long times=8000000;
for(;times>0;times--){
    //printf("times:%d\n",times);
#include "program3.c"
}
    exec(&vm);
    return 0;

}