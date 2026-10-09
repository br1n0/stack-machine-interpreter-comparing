// 
// i_TTC_dispatch_switch.c
// Token Threaded Code - dispatch imeplemented with switch: 
// compile && run:
// gcc i_TTC_dispatch_switch.c -lm -o i_TTC_dispatch_switch && ./i_TTC_dispatch_switch
// 

#include "Opcode_enum.c"
typedef struct VM VM;

#include "common.h"


// ===== EXEC =====
double exec(VM *vm){
    double a=0,b=0;


    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];

        switch(op){
            case OP_NOP:
                printf("pc=%d: OP_NOP\n", vm->pc - 1);
                break;

            case OP_RETURN:
                //printf("pc=%d: OP_RETURN R:%f\n", vm->pc - 1, vm->stack[0]);
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
    VM vm = {0};

 // long times=4000000;
    long times=400000;
    for(;times>0;times--){
        //printf("times:%d\n",times);
        #include "test3.c"
        exec(&vm);
    }

    return 0;
}