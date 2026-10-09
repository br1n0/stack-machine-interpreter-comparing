/*
stack commmon things
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define STACK_MAX 2*1024
#define OPCODE_MAX 2*1024



struct VM {
    uint16_t sp;
    uint16_t pc;
    uint16_t code_size;    
    double stack[ STACK_MAX ];
    Opcode code[ OPCODE_MAX ];
};



//static inline 
static inline __attribute__((always_inline))
double stack_pop(VM *vm){
//    assert(vm->sp > 0);
//    assert(vm->sp < STACK_MAX);

    double d= vm->stack[--vm->sp];
//    printf("stack_pop[%d]:%f\n", vm->sp,d );

    return d;
}


//static inline 
static inline __attribute__((always_inline))
void stack_push(VM *vm, double x){
//    printf("stack_push[%d]:%f\n", vm->sp+1,x );
//    assert(vm->sp < STACK_MAX);
    vm->stack[vm->sp++] = x;    
}
