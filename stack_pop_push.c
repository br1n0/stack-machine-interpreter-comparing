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
