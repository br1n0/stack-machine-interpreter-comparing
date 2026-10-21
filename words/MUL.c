

void MUL(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    b = stack_pop(vm);
    stack_push(vm, a*b);
}
