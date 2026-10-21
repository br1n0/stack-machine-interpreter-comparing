
void SUB(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
//    printf("pc=%d: OP_SUB\n", vm->pc-1);
    stack_push(vm, a-b);
}
