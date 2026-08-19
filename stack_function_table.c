/*
stack language, utilizzando function table 
esecuzione pratica in exex: table[op](vm);
voglio implementazione minimale

CODESTYLE:
poiche talvolta voglio commentare codice multilinea preferisco i commenti con //
preferisco utilizzare nella stessa linea { invece che accapo, per non generare troppoe linee

gcc stack_function_table.c -lm -o stack_function_table && ./stack_function_table
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// forward declaration
//typedef struct VM VM;


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
    OP_COS,

    OPCODE_COUNT
} Opcode;


// variabili globali supporto, forse converrebbe metterle nelle  funzioni, in questo modo il codice diverrebbe thread safe
double a=0,b=0;


typedef struct{
    double stack[ STACK_MAX ];
    Opcode code[ OPCODE_MAX ];
    int sp;
    int pc;
    int code_size;    
} VM;

void (*table[OPCODE_COUNT])(VM *vm);

static inline double stack_pop(VM *vm){
//    assert(vm->sp > 0);
//    assert(vm->sp < STACK_MAX);

    double d= vm->stack[--vm->sp];
//    printf("stack_pop[%d]:%f\n", vm->sp,d );

    return d;
}

static inline void stack_push(VM *vm, double x){
//    printf("stack_push[%d]:%f\n", vm->sp+1,x );
//    assert(vm->sp < STACK_MAX);
    vm->stack[vm->sp++] = x;    
}




// ======= opcode ======= 
void F_OP_NOP(VM *vm){
    printf("pc=%d: OP_NOP\n", vm->pc-1);
}


void F_OP_RETURN(VM *vm){
    printf("pc=%d: OP_RETURN R:%f\n",
           vm->pc-1,
           vm->stack[vm->sp-1]);

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








double exec(VM *vm){

    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];
        ( table[op] )( vm );
    }
    //return vm->stack[0];
    return vm->stack[vm->sp-1];
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

    exec( &vm );
*/

    VM vm = {0};
/*
    vm.stack[0]= +4;
    vm.stack[1]= +1;
    vm.stack[2]= +1;
    vm.stack[3]= +1;
    vm.stack[4]= 0;
    vm.sp = 5;

    vm.code[4]= OP_RETURN;
    vm.code[3]= OP_MUL;
    vm.code[2]= OP_SUB;
    vm.code[1]= OP_SUB;
    vm.code[0]= OP_SUB;
    vm.pc = 0;
    vm.code_size=5;
 */

long times=4000000;
for(;times>0;times--){
    //printf("times:%d\n",times);
#include "program3.c"
}    
    exec(&vm);
    return 0;
}