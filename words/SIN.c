
#include<math.h>

void SIN(VM *vm){
double a=0,b=0;
    a = stack_pop(vm);
    stack_push(vm, sin(a));
}
