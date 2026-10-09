// 
// stack language: switch based
// gcc stack_switch.c -lm -o stack_switch && ./stack_switch
// 

#include "Opcode_enum.c"
typedef struct VM VM;

#include "common.h"


// ===== EXEC =====
double exec(VM *vm){
    double a=0,b=0;

    while (vm->pc < vm->code_size) {
        Opcode op = vm->code[vm->pc++];

        if( op==OP_NOP )
            printf("pc=%d: OP_NOP\n", vm->pc - 1);

        if( op==OP_RETURN ){
            //printf("pc=%d: OP_RETURN R:%f\n", vm->pc - 1, vm->stack[0]);
            return vm->stack[0];
        }
        if( op==OP_ADD ){
            a = stack_pop(vm);
            b = stack_pop(vm);
            //printf("pc=%d: OP_ADD\n", vm->pc - 1);
            stack_push(vm, a + b);
        }
        if( op==OP_SUB ){
            a = stack_pop(vm);
            b = stack_pop(vm);
            //printf("pc=%d: OP_SUB\n", vm->pc - 1);
            stack_push(vm, a - b);
        }
        if( op==OP_MUL ){
            a = stack_pop(vm);
            b = stack_pop(vm);
            stack_push(vm, a * b);
        }
        if( op==OP_DIV ){
            a = stack_pop(vm);
            b = stack_pop(vm);
            stack_push(vm, a / b);
        }
        if( op==OP_SIN ){
            a = stack_pop(vm);
            stack_push(vm, sin(a));
        }
        if( op==OP_COS ){
            a = stack_pop(vm);
            stack_push(vm, cos(a));
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