/*
stack language, goto based
implementazione minimale
gcc stack_goto.c -lm -o stack_goto
gcc stack_goto.c -lm -o stack_goto && ./stack_goto

CODESTYLE:
poiche talvolta voglio commentare codice multilinea preferisco i commenti con //
preferisco utilizzare nella stessa linea { invece che accapo, per non generare troppoe linee

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
    //assert(vm->sp > 0);
    //assert(vm->sp < STACK_MAX);

    double d= vm->stack[--vm->sp];
    //printf("stack_pop[%d]:%f\n", vm->sp,d );

    return d;
}


static inline void stack_push(VM *vm, double x){
    //printf("stack_push[%d]:%f\n\n", vm->sp,x );
    //assert(vm->sp < STACK_MAX);
    vm->stack[vm->sp++] = x;    
}


void dump_exec_a_b( VM *vm,char *s, double a,double b){
        printf("pc=%d: %s\n", vm->pc - 1,s);
        printf("a:%f\n",a);
        printf("b:%f\n",b);
}


double exec(VM *vm){
    double a=0,b=0,r=0;
    Opcode op;

    OP_NOP:
        a=b=0;
        dump_exec_a_b(vm,"OP_NOP",a,b);
        printf("\n");
        goto OP_NEXT;

    OP_RETURN:
        a=b=0;
        //dump_exec_a_b(vm,"OP_RETURN",a,b);
        printf("RV:%f\n", vm->stack[0]);
        goto END;

    OP_ADD:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r= a + b;
        stack_push(vm, r);
        //dump_exec_a_b(vm,"OP_ADD",a,b);
        goto OP_NEXT;

    OP_SUB:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r= a - b;
        //dump_exec_a_b(vm,"OP_SUB",a,b);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_MUL:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r= a * b;
        //dump_exec_a_b(vm,"OP_MUL",a,b);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_DIV:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r= a/b;
        //dump_exec_a_b(vm,"OP_DIV",a,b);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_SIN:
        a = stack_pop(vm);
        b= 0;
        r= sin(a);
        //dump_exec_a_b(vm,"OP_SIN",a,b);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_COS:
        a = stack_pop(vm);
        b= 0;
        r= cos(a);
        //dump_exec_a_b(vm,"OP_COS",a,b);
        stack_push(vm, r );
        goto OP_NEXT;


/*
modo standard
switch(op){
case OP_NOP:    goto L_NOP;
case OP_RETURN: goto L_RETURN;
case OP_ADD:    goto L_ADD;
case OP_SUB:    goto L_SUB;
case OP_MUL:    goto L_MUL;
case OP_DIV:    goto L_DIV;
case OP_SIN:    goto L_SIN;
case OP_COS:    goto L_COS;
}
*/


    //static void *dispatch[] = {
    static const void *dispatch[] = {    
        &&OP_NOP,
        &&OP_RETURN,
        &&OP_ADD,
        &&OP_SUB,
        &&OP_MUL,
        &&OP_DIV,
        &&OP_SIN,
        &&OP_COS
    };


    OP_NEXT:
        if(vm->pc >= vm->code_size)
            goto END;

        op = vm->code[vm->pc++];

        //assert(op >= 0 && op < sizeof(dispatch)/sizeof(dispatch[0]));
        //assert((unsigned)op < sizeof(dispatch)/sizeof(dispatch[0]));
        //eviti un salto verso memoria casuale se il bytecode è corrotto.
        
        goto *dispatch[op];

        //si puo fare a meno di op
        goto *dispatch[ vm->code[vm->pc++] ];


    END:
        //return vm->stack[0];
        return vm->stack[vm->sp - 1];

}

int main(){
    /*
    VM vm = {0}; //resetto vm, dato che nop corrisponde a 0
    
    vm.stack[0]= 0;
    vm.stack[1]= 1;
    vm.stack[2]= 1;
    vm.stack[3]= 1;
    vm.stack[4]= 2;
    vm.sp = 4;

    vm.code_size=4;

    vm.code[0]= OP_SUB;
    vm.code[1]= OP_SUB;
    vm.code[1]= OP_SUB;
    vm.code[3]= OP_MUL;


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