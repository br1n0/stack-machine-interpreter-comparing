// 
// stack language: goto based
// gcc stack_goto.c -lm -o stack_goto
// 

#include "Opcode_enum.c"
typedef struct VM VM;

#include "stack_common.h"


void dump_exec_a_b( VM *vm,char *s, double a,double b){
        printf("pc=%d: %s\n", vm->pc - 1,s);
        printf("a:%f\n",a);
        printf("b:%f\n",b);
}


// ===== EXEC =====
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


    //questa implementazione usa una dispatch table tramite un estensione di c di gcc
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
    VM vm = {0};

    long times=4000000;
    for(;times>0;times--){
        //printf("times:%d\n",times);
        #include "program3.c"
    }

    exec(&vm);

    return 0;
}