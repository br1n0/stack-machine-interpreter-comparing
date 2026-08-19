/*
stack language, subroutine threaded
implementazione minimale

CODESTYLE:
poiche talvolta voglio commentare codice multilinea preferisco i commenti con //
preferisco utilizzare nella stessa linea { invece che accapo, per non generare troppe linee


gcc stack_soubroutine1.c -lm -o stack_subroutineS
gcc stack_soubroutine1.c -lm -o stack_subroutine && ./stack_subroutine
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define STACK_MAX 2*1024
#define OPCODE_MAX 2*1024


// forward declaration
typedef struct VM VM;


// definisco un tipo puntatore a funzione void f(VM*)
typedef void (*Opcode)(VM *vm);


// struttura VM
struct VM {
    double stack[STACK_MAX];
    Opcode code[OPCODE_MAX];

    int sp;
    int pc;
    int code_size;
};




// stack

static inline double stack_pop(VM *vm){
//    assert(vm->sp > 0);
    double d = vm->stack[--vm->sp];
    //printf("stack_pop[%d]: %f\n", vm->sp, d);
    return d;
}


static inline void stack_push(VM *vm, double x){
//    assert(vm->sp < STACK_MAX);
//    printf("stack_push[%d]: %f\n", vm->sp, x);
    vm->stack[vm->sp++] = x;
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


// interprete threaded
void exec(VM *vm){
    while(vm->pc < vm->code_size){
        Opcode op = vm->code[vm->pc++];
        op(vm);
    }
}


int main(){
//  VM vm = {0};
/*
    // stack iniziale:
    //
    // (((7+19)+5)-3)

    stack_push(&vm,7);
    stack_push(&vm,19);
    stack_push(&vm,5);
    stack_push(&vm,3);

    // programma:
    //
    // OP_ADD
    // OP_ADD
    // OP_SUB
    // OP_RETURN
    vm.code[0] = OP_ADD;
    vm.code[1] = OP_ADD;
    vm.code[2] = OP_SUB;
    vm.code[3] = OP_RETURN;

    vm.code_size = 4;
    vm.pc = 0;
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

/*
Output atteso:

stack_push[0]: 7.000000
stack_push[1]: 19.000000
stack_push[2]: 5.000000
stack_push[3]: 3.000000
stack_pop[3]: 3.000000
stack_pop[2]: 5.000000
pc=2: OP_SUB
stack_push[2]: 2.000000
stack_pop[2]: 2.000000
stack_pop[1]: 26.000000
pc=1: OP_ADD
stack_push[1]: 28.000000
stack_pop[1]: 28.000000
stack_pop[0]: 7.000000
pc=0: OP_ADD
stack_push[0]: 35.000000
pc=3: OP_RETURN R:35.000000

Questa è la forma classica subroutine threaded: il bytecode non contiene numeri di opcode, ma direttamente indirizzi di funzione.

Una possibile evoluzione successiva è separare:

    code space (Opcode code[])

    data stack

    return stack

    opcode tipo LIT per inserire costanti nel bytecode

ottenendo una struttura molto vicina a un piccolo interprete Forth.
*/

