
void RETURN(VM *vm){
    double a=0,b=0;
    //printf("pc=%d: OP_RETURN R:%f\n",  vm->pc-1,  vm->stack[vm->sp-1]);

    vm->pc = vm->code_size; // termina VM
}
