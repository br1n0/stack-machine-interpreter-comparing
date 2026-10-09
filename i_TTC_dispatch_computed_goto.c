// 
// i_TTC_dispatch_goto.c
// Token Threaded Code - dispatch imeplemented with goto: 
// compile && run:
// gcc i_TTC_dispatch_goto.c -lm -o i_TTC_dispatch_goto && ./i_TTC_dispatch_goto
// 

#include "Opcode_enum.c"
typedef struct VM VM;

#include "common.h"


void dump_exec_a_b( VM *vm,char *s, double a,double b){
        printf("pc=%d: %s\n", vm->pc - 1,s);
        printf("a:%f\n",a);
        printf("b:%f\n",b);
}




double exec(VM *vm){
    double a=0, b=0, r=0;
    Opcode op;

    // dispatch table: puo' stare qui, l'importante e' che venga
    // definita prima di essere usata da OP_NEXT (le label &&Label
    // sono risolte a compile time, quindi la posizione nel testo
    // non ha effetti sull'ordine di esecuzione)
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

    // punto di ingresso VERO della funzione:
    // senza questo goto, l'esecuzione cadrebbe per fall-through
    // dentro OP_NOP qui sotto, eseguendolo sempre una volta,
    // indipendentemente dal contenuto di vm->code[0]
    goto OP_NEXT;

    OP_NOP:
        a=b=0;
        dump_exec_a_b(vm,"OP_NOP-G",a,b);
        printf("SP:%d\n",vm->sp);
        printf("\n");
        goto OP_NEXT;

    OP_RETURN:
//        a=b=0;
            a = stack_pop(vm);

        //dump_exec_a_b(vm,"OP_RETURN-G",a,b);
        goto END;

    OP_ADD:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r = a + b;
        stack_push(vm, r);
        goto OP_NEXT;

    OP_SUB:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r = a - b;
        stack_push(vm, r);
        goto OP_NEXT;

    OP_MUL:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r = a * b;
        stack_push(vm, r);
        goto OP_NEXT;

    OP_DIV:
        a = stack_pop(vm);
        b = stack_pop(vm);
        r = a / b;
        stack_push(vm, r);
        goto OP_NEXT;

    OP_SIN:
        a = stack_pop(vm);
        b = 0;
        r = sin(a);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_COS:
        a = stack_pop(vm);
        b = 0;
        r = cos(a);
        stack_push(vm, r);
        goto OP_NEXT;

    OP_NEXT:
        // condizione corretta: esci quando pc ha raggiunto la fine
        // del bytecode (prima era "<=" e faceva uscire subito)
        if (vm->pc >= vm->code_size)
            goto END;
        op = vm->code[vm->pc++];
        goto *dispatch[op];

    END:
        return vm->stack[vm->sp - 1];
}


int main(){
    VM vm = {0};

    long times=400000;
    //times=1;
    for(;times>0;times--){
        //printf("times:%d\n",times);
        #include "test3.c"
        exec(&vm);
    }


    return 0;
}